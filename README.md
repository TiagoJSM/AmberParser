# Amber Parser

A C++ parsing tool to auto generate instrospection code to improve development of [Amber Engine](https://github.com/TiagoJSM/AmberEngine).
The purpose behind this is to achieve similar syntax as Unity3D and Unreal Engine 4 for instrospection and serialization.

## Builds

[![Visual Studio Builds](https://ci.appveyor.com/api/projects/status/32r7s2skrgm9ubva/branch/master?svg=true)](https://ci.appveyor.com/project/TiagoJSM/amberparser/branch/master) Windows (Visual Studio 2017 / 2015)

[![Linux clang & g++](https://travis-ci.com/TiagoJSM/AmberParser.svg?branch=master)](https://travis-ci.com/TiagoJSM/AmberParser) Linux clang & g++

## Getting Started

* Download project
* Run ```git submodule update --init --recursive --remote``` to get submodule dependencies

### Prerequisites

* Install C++ toolchain of choice

### Installing

* Run: "cmake ." to generate project files
OR
* Run: "cmake --build "./build" --config Debug --target AmberParser" to generate executable

## Running the tests

* No tests for now, they will come in the future

## Authors

* **Tiago Martins** - [TiagoJSM](https://github.com/TiagoJSM)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
