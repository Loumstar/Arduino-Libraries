# Arduino Library

## Introduction

This is a repository of all my own-written libraries for the arduino in C18.
Most will not be fully complete, but will likely be expanded in the future.

## Installing

Download the repository using git clone:

```bash
git clone git@github.com:Loumstar/Arduino-Libraries.git
```

To allow the Arduino IDE to recognise the modules, transfer all files within the repo directory to:

```bash
~/Documents/Arduino/libraries/
```

Check they exist by opening the Arduino IDE and going to: <br>
`Sketch/Include Library/Contributed Libraries/`.

If they exist, they are ready to be added to your sketches.

For information on installing libraries, see: http://www.arduino.cc/en/Guide/Libraries

## Usage

Like with any header file, add the module to your sketch by using the `#include` qualifier:

```c
#include <complex.lite.h>
```

If the module does not have any documentation, read the code used in the test scripts.

## Contact

If you have any questions or have any suggestions to improve the repository, please email me at louis.manestar@gmail.com.

## License

MIT License

Copyright (c) 2019 Louis E Manestar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
