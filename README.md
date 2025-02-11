# Dragon

Dragon is a build tool and interpreter designed to be easier to use than CMake/Make, supporting multiple programming languages like C and Python.

## Features

- **Multi-language support**: Support for C, Python, and more.
- **Native library usage**: Utilizes native libraries of each language.
- **Ease of use**: Easier to use than CMake/Make.


## Installation

To compile the Dragon interpreter, run:

```sh
gcc src/Dragon.c -o Dragon
Usage
Create a .DragonC file to define your variables and commands. Here is an example:

plaintext
# Variable definitions
COMPILER=gcc
CFLAGS=-Wall -O2

# Commands
build:
    $COMPILER src/main.c src/utils.c -o build/output $CFLAGS
clean:
    if [ -d build ]; then rm -rf build/*; else if exist build\* del /Q build\*; fi
Then, to use Dragon, run:

sh
./Dragon .DragonC
```
## License
This project is licensed under the MIT License - see the LICENSE file for details.