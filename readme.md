Terra
=

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Build Status](https://travis-ci.com/majestic53/terra.svg?branch=master)](https://travis-ci.com/majestic53/terra)

A procedural terrain generator

Table of Contents
=

1. [About](https://github.com/majestic53/terra#about) -- About the project
2. [Building](https://github.com/majestic53/terra#building) -- How to build the project
3. [Changelog](https://github.com/majestic53/terra#changelog) -- Log of project changes

About
=

The project is implemented in C++ and exposes a simple API, described in ```include/terra.h``` and ```lib/libterra.a```.

For an example usage of this API, see the launcher tool, under ```tool/```.

Building
=

__NOTE__: Tested under MacOS with the GCC/Clang C++ compilers. Modification to the makefiles might be required to build with a different OS/compiler.

### Building from Makefile

#### Arguments

Run the following commands from the projects root directory:

```
$ export CXX=<COMPILER>
$ make <BUILD_TYPE>
```

Where COMPILER corrisponds to either ```clang++``` or ```g++```

Where BUILD_TYPE corrisponds to either ```release``` or ```debug```

#### Optional Arguments

To build with tracing enabled, run the following command from the project's root directory:

```
$ make TRACE=<LEVEL>
```

Where LEVEL corrisponds to the tracing verbosity (0=Off, 1=Error, 2=Warnings, 3=Information, 4=Verbose)

#### Examples

The following example shows how to build the release project, under the Clang C++ compiler:

```
$ export CXX=clang++
$ make release
```

The following example shows how to build the debug project with informational tracing, under the GCC C++ compiler:

```
$ export CXX=gcc
$ make TRACE=3
```

Changelog
=

Version 0.1.1932
-

*Updated: 8/11/2019*

* Added mousewheel zooming
* Added world class

*Updated: 8/10/2019*

* Added generator/perlin class
* Added display class

*Updated: 8/9/2019*

* Initial commit

*Changelog truncated (see file history for full log)*
