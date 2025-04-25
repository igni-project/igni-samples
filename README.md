# igni-samples

A set of programs that showcase the Igni computing environment

## Running the Program

If a SUP display manager is already installed and active, simply run the built executable in `src/`. If no such display manager is available, 

1. Clone, build and install [ignition](https://github.com/igni-project/ignition) as instructed in its README file.

2. Run the `testrun` script in the root directory of this repository.

## Prerequisites

Specialised software is required in order to compile this source code. If one or more prerequisites are not installed, the final executable may not build or lack certain features.

### Autotools

[GNU Autotools](https://en.wikipedia.org/wiki/GNU_Autotools) is readily
available on most linux systems package managers.

- Arch Linux: `sudo pacman -Syu autoconf automake libtool`
- Debian and Ubuntu: `sudo apt-get install -y autotools-dev autoconf`
- Fedora: `sudo dnf install autoconf automake`

### libsup

[libsup](https://github.com/igni-project/libsup) is not currently available on any major package repositories and must be built and installed from source.

1. Ensure Autotools is installed before proceeding.

2. Clone libsup with a Git client of your choice. With the [official git command-line client](https://git-scm.com/downloads/linux), this will be `git clone https://github.com/igni-project/libsup.git`.

3. Open a terminal in the root folder of the libsup repository and run the command `./bootstrap && ./configure && make && sudo make install`.

## Build Instructions

run the command `./bootstrap && ./configure && make && sudo make install`.



