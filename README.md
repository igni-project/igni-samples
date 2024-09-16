# igni-samples

Basic Igni demonstrations and tests

## Installation

### Prerequisites

* a C compiler
* [igni-server](https://github.com/igni-project/igni-server)
* [libigni](https://github.com/igni-project/libigni)
* [make](https://www.gnu.org/software/make)
* [autoconf](https://www.gnu.org/software/autoconf)
* [automake](https://www.gnu.org/software/automake)


### Instructions

1. Open up a terminal (if you haven't already) and go to the root directory
of this repository.
2. Type the commands `./configure`, `make` and `make install`.

## Test Run

Each subdirectory in this repository has a script named `testrun`. This script
sets up environment variables before executing its program.

To test a sample, start igni-render then run the `testrun` script in the sample
subdirectory of your choosing.

