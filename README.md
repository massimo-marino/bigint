# bigint

C++17 implementation of arbitrary precision integer arithmetic.


This implementation is a 'fork' from:
https://sites.google.com/site/indy256/algo_cpp/bigint


## Requirements

`cmake` is used to compile the sources.

The default compiler used is `clang++-9.0`.

The cmake files compile with `-std=c++17`.

The unit tests are implemented in `googletest`: be sure you have installed `googletest` to compile.


## Install and Run Unit Tests

```bash
$ git clone https://github.com:massimo-marino/bigint.git
$ cd bigint
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd src/unitTests
$ ./unitTests
```


## How to Use it

See the source code and the unit tests for examples of use.
