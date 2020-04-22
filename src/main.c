/*This is the sample program to notify us for the file creation and file deletion takes place in “/tmp” directory*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

static const char downloads_dir_default[] = "Downloads";
static char downloads_dir[4096];

static int inotify_instance = -1;
static char event_buffer[EVENT_BUF_LEN];
static int watch_list;

int main()
{
	/* Get downloads directory. */
	FILE *xdg_cmd = NULL;
	xdg_cmd = popen("xdg-user-dir DOWNLOAD", "r");
	if (!xdg_cmd) {
		/* Default Download folder */
		char *home_dir = getenv("HOME");
		if (!home_dir) {
			struct passwd *pw = getpwuid(getuid());
			if (!pw)
				perror("Failed to get home directory!");
			home_dir = pw->pw_dir;
			if (!home_dir)
				perror("Failed miserably to get downloads directory!");
		}
		strcat(downloads_dir, home_dir);
		strcat(downloads_dir, "/");
		strcat(downloads_dir, downloads_dir_default);
	} else {
		/* Read path from output of xdg */
		int c, n = 0;
		while ((c = fgetc(xdg_cmd)) != EOF) {
			if (c == '\n')
				downloads_dir[n++] = '\0';
			else
				downloads_dir[n++] = (char)c;
		}
		downloads_dir[n] = '\0';

		pclose(xdg_cmd);
	}

	/* Initialize inotify instance */
	inotify_instance = inotify_init();
	if (!inotify_instance)
		perror("Failed initializing inotify library!");

	/* Add wanted Downloads to watchlist  */
	watch_list = inotify_add_watch(inotify_instance, downloads_dir,
				       IN_CREATE | IN_DELETE);
	if (!watch_list)
		perror("Failed to add downloads folder to watchlist!");

	/* Get events*/
	int length = read(inotify_instance, event_buffer, EVENT_BUF_LEN);
	if (!length)
		perror("Failed to read inotify buffer!");

	/* Process events */
	int i = 0;
	while (i < length) {
		struct inotify_event *event =
			(struct inotify_event *)&event_buffer[i];
		if (event->len) {
			if (event->mask & IN_CREATE) {
				if (event->mask & IN_ISDIR) {
					printf("New directory %s created.\n",
					       event->name);
				} else {
					printf("New file %s created.\n",
					       event->name);
				}
			} else if (event->mask & IN_DELETE) {
				if (event->mask & IN_ISDIR) {
					printf("Directory %s deleted.\n",
					       event->name);
				} else {
					printf("File %s deleted.\n",
					       event->name);
				}
			}
		}
		i += EVENT_SIZE + event->len;
	}
	inotify_rm_watch(inotify_instance, watch_list);

	close(inotify_instance);
}
