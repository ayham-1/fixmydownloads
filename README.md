![CI](https://github.com/realaltffour/fixmydownloads/workflows/CI/badge.svg?branch=master&event=push) 
# fixmydownloads
</br>
The goal of the project is to make the simplest downloads folder organizer that is configured by code(defaults are more than enough), making it so small that the whole thing fits in one file!

## Installation
Their are multiple ways you can install it. Grab your distro's package from the release section and install it! Or wait for the project to get into your distro repositories (hopefully).

## Compiling from Source

Using docker is the recommended way, make sure you have the correct permissions to use docker.
```shell
$ ./buildDocker.sh (For debbuggable binary and installers)
$ ./buildDockerRelease.sh (For releasable binary and installers)
$ ./buildArtifacts.sh (For extracting installers into $(PROJECT)/artifacts
```

In Linux with a ready ```C``` development environment, run:
```shell
$ ./build.sh (For debuggable binary)
$ ./buildRelease.sh (For release binary)
```
The binary is outputted into ```$(PROJECT)/bin```

## Technical Overview
### Overview
The program runs in the background, watching the downloads folder with ```inotify``` and copies any new files detected, based on extension of the file, to documents folder. All folders are by default sent to documents/misc. The projects applies to [XDG File directory specification](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html).

### Starting up the application
The installers install the systemd/OpenRC service by default. Ex: ```.deb``` file installs ```systemd```, ```.ebuild``` file installs ```OpenRC``` service. Compiling from source gives you the option to specify the service installed. This section is not complete. Instructions should be provided to install each of the services.

### Configuring
This section is not complete, so is the application. But the main idea is to have defines that control the behavor of the application (specifing extensions to directory, documents/downloads location, etc). The defualt configuration should be enough though.

### Built With

* [C](https://en.wikipedia.org/wiki/C_programming_language) - Language used.
* [inotify](https://en.wikipedia.org/wiki/Inotify) - Linux library used for watching files.
* [systemD](https://en.wikipedia.org/wiki/Systemd) - *Optional* Start-up mechanism, only installed with installers.
* [OpenRC](https://en.wikipedia.org/wiki/OpenRC) - *Optional* Start-up mechanism, only installed with installers.

## Authors

* **altffour** - *Initial work* - [realaltffour](https://github.com/realaltffour)

## License
This project is licensed under the GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details.

## Inspiring
I never found a downloads folder organizer that is so simple that you just install it and forget about it. Adding, I wanted to a project that would be (suckless-compatible)[https://suckless.org/] (if that exists). It's worthy to note that I made a 5-minute research 'session' about download organizer for Linux and didn't find any. Therefore I called this project the simplest.
