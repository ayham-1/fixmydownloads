![CI](https://github.com/realaltffour/fixmydownloads/workflows/CI/badge.svg?branch=master&event=push) 
# fixmydownloads
</br>
The goal of the project is to make the simplest downloads folder organizer that is configured by code making it so small that the whole thing fits in one file! Eliminating the need to manually organize or clean up your downloads folder!

## Organizing your current download directory
To organize your current downloads directory, run after installation:
```shell
$ ./fixmydl all
```
No return means success.
Note: that this completely cleans your downloads directory.

## Installation
Their are multiple ways you can install it. Grab your distro's package from the release section and install it! Or wait for the project to get into your distro repositories (hopefully).

## Compiling from Source

Using docker is the recommended way, make sure you have the correct permissions to use docker.
```shell
$ ./buildDocker.sh (For debbuggable binary and installers)
$ ./buildDockerRelease.sh (For releasable binary and installers)
$ ./buildArtifacts.sh (For extracting installers into $(PROJECT)/artifacts)
```

In Linux with a ready ```C``` development environment, run:
```shell
$ ./build.sh (For debuggable binary)
$ ./buildRelease.sh (For release binary)
```
The binary is outputted into ```$(PROJECT)/bin```
Refer to [this section](#starting-up-the-application) for setting up the application to run on login.

## Technical Overview
### Overview
The program runs in the background, watching the downloads folder with ```inotify``` and copies any new files detected, based on extension of the file, to documents folder. All folders are by default sent to documents/prefix/misc. The projects applies to [XDG File directory specification](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html). By default, the prefix is `orgdl`.

### Starting up the application
To make `fixmydl` run when you login run:
```shell
$ echo 'fixmydl' >> ~/.profile
```

### Configuring
There are multiple configuration options present.

#### Extension ignore list
In file `main.c`, adding values to element `extension_ignore_list` will make sure that the application doesn't organize these extensions. For example, by default element: `crdownloads` is added to ignore temp files that chromium/Chrome uses while downloading content.
```C
/* Example addition */
static const int IGNORE_LIST_SIZE = 2; /* MAKE SURE TO UPDATE THIS */
static const char *extension_ignore_list[] = { "crdownload", "tmp" }; /* Don't add dot */
```
Notes:
   - Make sure you update `IGNORE_LIST_SIZE`
   - Make sure you don't add dot for the `extension_ignore_list`
   
#### Prefix Directory
This is the name or sub-path to where the categories should be placed in the documents directory. By default, it is set to `orgdl`. Ex: `.txt` files should be placed into `$HOME/$DOCS/orgdl/txt`. To disable this, set it's value to `""`
```C
/* Example change */
static const char prefix_dir[] = "organize/folder"; /* Do not end with trailing forward-slashes. */
/* Example disable */
static const char prefix_dir[] = "";
```
Note:
  - Make sure you don't end `prefix_dir` with trailing forward-slashes.
 
#### Miscellaneous Directory
This is the name of the directory where file and folder without a name are placed. By default, it's set to `misc`. Example: `test` is placed into `$HOME/$DOCS/$sprefix_dir/misc/`
```C
/* Example change*/
static const char misc_dir_default[] = "miscellaneous"; /* Do not end with trailing forward-slashes. */
```
Note:
  - Make sure you don't end `misc_dir_default[]` with trailing forward-slashes.

#### Downloads & Documents Directories
If automatic checking of `XDG` fails, the program falls back to `pwd struct` method. If that fails too, then it defaults to `downloads_dir_default[]` and `documents_dir_default[]` respectively. By default, `downloads_dir_default[]` is set to `Downloads`, and `documents_dir_defaults[]` is set to `Documents`, relative to `$HOME`.
```C
/* Default Downloads change example */
static const char downloads_dir_default[] = "dl"; /* Do not end with trailing forward-slashes */
/* Default Documents change example */
static const char documents_dir_default[] = "dox"; /* Do not end with trailing forward-slashes */
```
Note:
  - Make sure you don't end `downloads_dir_default[]` or `documents_dir_default[]` with trailing forward-slashes.

#### Advanced Configuration
This section is dedicated of the configuration of how the application operates in a low level. It won't be noticed for the average user.

##### EVENT_BUF_LEN
The application should consume very little memory. Options like `EVENT_BUF_LEN` can be used to limit the amount of events read per iteration of the main while loop.
```C
/* Example change */
#define EVENT_BUF_LEN (512 * (EVENT_SIZE + 16))
```
##### PATH_BUF_LEN
This is the amount of bytes to allocate for path buffers. Usually, `ext4` supports upto `4096` characters. Which is the default.
```C
/* Example change */
#define PATH_BUF_LEN 3072
```
##### CMD_BUF_LEN
This is the amount of bytes to allocate for command line buffers. It's a must for it to be atleast 2 times the size of `PATH_BUF_LEN` and a little more room, because move operations use command line.
```C
/* Example change */
#define CMD_BUF_LEN ((PATH_BUF_LEN * 2) * 1.1) /* Do not remove the brackets. */
```

### Built With

* [C](https://en.wikipedia.org/wiki/C_programming_language) - Language used.
* [inotify](https://en.wikipedia.org/wiki/Inotify) - Linux library used for watching files.

## Authors

* **altffour** - *Initial work* - [realaltffour](https://github.com/realaltffour)

## License
This project is licensed under the GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details.

## Inspiring
I never found a downloads folder organizer that is so simple that you just install it and forget about it. Adding, I wanted to a project that would be [suckless-compatible](https://suckless.org/) (if that exists). It's worthy to note that I made a 5-minute research 'session' about download organizer for Linux and didn't find any. Therefore I called this project the simplest.

----------------
README.md valid for version `1.3.0`
