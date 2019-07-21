# Arduino Library

## Introduction

This is a repository of all my own-written libraries for the arduino in C18.
Most will not be fully complete, but will likely be expanded in the future.

For information on installing libraries, see: http://www.arduino.cc/en/Guide/Libraries

## Installing

Download the repository using git clone:

```bash
git clone git@github.com:Loumstar/Arduino-Libraries.git
```

To allow the Arduino IDE to recognise the modules, transfer all files within the repo directory to:

```bash
~/Documents/Arduino/libraries/
```

Check they exist by opening the Arduino IDE and going to:
`Sketch/IncludeLibrary/ContributedLibraries`.

If they exist, they are ready to be added to your sketches.

## Usage

Like with any header file, add the module to your sketch by using the `#include` qualifier:

```c
#include <complex.lite.h>
```

If the module does not have any documentation, read the code used in the test scripts.

## Contact

If you have any questions or have any suggestions to improve the repository, email me at louis.manestar@gmail.com.