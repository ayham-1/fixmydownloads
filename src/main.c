#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

static const int IGNORE_LIST_SIZE = 1;
static const char *extension_ignore_list[] = { "crdownload\0" };

static const char misc_dir_default[] = "misc";

static const char downloads_dir_default[] = "Downloads";
static char *downloads_dir;

static const char documents_dir_default[] = "Documents";
static char *documents_dir;

static int inotify_instance = -1;
static char event_buffer[EVENT_BUF_LEN];
static int watch_list;

char *strrev(char *str);
char *get_directory(const char *param);
char *get_extension(const char *name);
char *pad_unique_chars(const char *str);
void move(const char *name);

int main(int argc, char *argv[])
{
	/* Get Downloads directory Location */
	downloads_dir = get_directory("DOWNLOAD");

	/* Get Documents directory Location */
	documents_dir = get_directory("DOCUMENTS");

	/* Initialize inotify instance */
	inotify_instance = inotify_init();
	if (!inotify_instance)
		perror("Failed initializing inotify library!");

	/* Add wanted Downloads to watchlist  */
	watch_list =
		inotify_add_watch(inotify_instance, downloads_dir, IN_CREATE);
	if (!watch_list)
		perror("Failed to add downloads folder to watchlist!");

	/* Loop till we die. */
	while (1) {
		/* Get events*/
		int length =
			read(inotify_instance, event_buffer, EVENT_BUF_LEN);
		if (!length)
			perror("Failed to read inotify buffer!");

		/* Process events */
		int i = 0;
		while (i < length) {
			struct inotify_event *event =
				(struct inotify_event *)&event_buffer[i];
			if (event->len) {
				if (event->mask & IN_CREATE)
					move(event->name);
			}
			i += EVENT_SIZE + event->len;
		}
	}
	inotify_rm_watch(inotify_instance, watch_list);

	close(inotify_instance);
}

void move(const char *name)
{
	/* Get all variables needed */
	char *ext = get_extension(name);
	char *dest = (char *)malloc(4096 * sizeof(char));
	sprintf(dest, "%s/%s/%s", documents_dir, ext, name);
	char *src = (char *)malloc(4096 * sizeof(char));
	sprintf(src, "%s/%s", downloads_dir, name);
	char *org = (char *)malloc(4096 * sizeof(char));
	sprintf(org, "%s/%s/", documents_dir, ext);

	/* Check if extension is ignored */
	for (unsigned int i = 0; i < IGNORE_LIST_SIZE; i++) {
		if (strcmp(extension_ignore_list[i], ext) == 0)
			return;
	}

	/* Ensure/Create directories for organization */
	char *cmd = (char *)malloc(8096 * 2.5 * sizeof(char));
	strcat(cmd, "mkdir --parents \"");
	strcat(cmd, org);
	strcat(cmd, "\"\0");
	if (system(pad_unique_chars(cmd)))
		perror("Did not create directories, they maybe already present!");

	printf("Moving: %s Extension: %s\n", name, ext);
	memset(cmd, 0, strlen(cmd));
	strcat(cmd, "mv ");
	strcat(cmd, pad_unique_chars(src));
	strcat(cmd, " ");
	strcat(cmd, pad_unique_chars(dest));
	strcat(cmd, "\0");
	if (system(cmd))
		perror("Failed to move file!");
}

char *get_extension(const char *name)
{
	char *ext = (char *)malloc(sizeof(misc_dir_default));
	strcpy(ext, misc_dir_default); /* Set default misc directory */
	int ext_len = 0;
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] == '.') {
			for (int j = i + 1; j < strlen(name); j++) {
				ext = (char *)realloc(ext, ++ext_len);
				ext[ext_len - 1] = name[j];
			}
			ext = (char *)realloc(ext, ++ext_len);
			ext[ext_len - 1] = '\0';
			break;
		}
	}
	return ext;
}

char *get_directory(const char *name)
{
	char *result = (char *)malloc(4096 * sizeof(char));
	FILE *xdg_cmd = NULL;
	char *cmd = (char *)malloc(20 * sizeof(char));
	sprintf(cmd, "xdg-user-dir %s", name);
	xdg_cmd = popen(cmd, "r");
	if (!xdg_cmd) {
		char *home_dir = getenv("HOME");
		if (!home_dir) {
			struct passwd *pw = getpwuid(getuid());
			if (!pw)
				perror("Failed to get home directory!");
			home_dir = pw->pw_dir;
			if (!home_dir)
				perror("Failed miserably to get a directory path!");
		}
		strcat(result, home_dir);
		strcat(result, "/");
		if (strcmp(name, "DOWNLOAD") == 0)
			strcat(result, downloads_dir_default);
		else if (strcmp(name, "DOCUMENTS") == 0)
			strcat(result, documents_dir_default);
	} else {
		/* Read path from output of xdg */
		int c, n = 0;
		while ((c = fgetc(xdg_cmd)) != EOF) {
			if (c == '\n')
				result[n++] = '\0';
			else
				result[n++] = (char)c;
		}
		result[n] = '\0';

		pclose(xdg_cmd);
	}
	return result;
}

char *strrev(char *str)
{
	char *p1, *p2;

	if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

char *pad_unique_chars(const char *str)
{
	char *result = (char *)malloc(sizeof(char));
	int counter = 0;
	memset(result, 0L, sizeof(char));
	for (unsigned int i = 0; i < strlen(str); i++) {
		if (str[i] == '(' || str[i] == ')') {
			result = (char *)realloc(result, counter + 2);
			result[counter++] = 92;
			result[counter++] = str[i];
		} else if (str[i] == ' ') {
			result = (char *)realloc(result, counter + 2);
			result[counter++] = 92;
			result[counter++] = str[i];
		} else {
			result = (char *)realloc(result, counter + 1);
			result[counter++] = str[i];
		}
	}
	result = (char *)realloc(result, sizeof(char) * counter + 1);
	result[counter] = '\0';
	return result;
}
