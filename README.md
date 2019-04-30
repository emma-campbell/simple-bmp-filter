# Simple BMP Filter

A simple program for filtering BMP images! Implemented in C++ and built using cmake! 

Let's look at the structure of the project

```bash
.
├── CMakeLists.txt
├── README.md
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.13.3
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeSystem.cmake
│   │   │   └── CompilerIdCXX
│   │   │       ├── CMakeCXXCompilerId.cpp
│   │   │       ├── a.out
│   │   │       └── tmp
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── CMakeOutput.log
│   │   ├── CMakeTmp
│   │   ├── Makefile.cmake
│   │   ├── Makefile2
│   │   ├── TargetDirectories.txt
│   │   ├── bmp-filter.dir
│   │   │   ├── CXX.includecache
│   │   │   ├── DependInfo.cmake
│   │   │   ├── build.make
│   │   │   ├── cmake_clean.cmake
│   │   │   ├── depend.internal
│   │   │   ├── depend.make
│   │   │   ├── flags.make
│   │   │   ├── link.txt
│   │   │   ├── progress.make
│   │   │   └── src
│   │   │       └── main.cpp.o
│   │   ├── cmake.check_cache
│   │   ├── feature_tests.bin
│   │   ├── feature_tests.cxx
│   │   └── progress.marks
│   ├── Makefile
│   ├── bmp-filter
│   └── cmake_install.cmake
├── include
│   └── bmp.hpp
├── new_red_tele.bmp
├── red_tele.bmp
├── red_tele_new.bmp
└── src
    ├── bmp.cpp
    └── main.cpp
```

The raw files (C++ and headers) are found in the directories `src` and `include`. `incude` contains the header file the `BMP` class, and `src` contains the executable (*.cpp) for `BMP`, as well as the main program `main.cpp`. These are the files you will want to grade for code quality. 

If you want to see the program in action, you're going to want to run `cprocess` in the `build` directory.

## Running the Program

First, clone this directory using the command: 
```bash
git clone https://github.com/emma-campbell/simple-bmp-filter
```

After that, change directories into `build` using the command:
```bash
cd build
```

Once you are there, you will be able to run the exectuable using the basic scheme
```bash
./bmp-filter <infile> <outfile>
```
where `<infile>` is the relative path to the bmp image you wish to filter, and `<outfile>` is the location where you wish to save the filtered product.

Or, if you wish to use the included examples:
```bash
./bmp-filter ../red_tele.bmp ../new_red_tele.bmp
```

After running the previous command, if you look in the main directory you will find a new file `new_red_tele.bmp`, which contains the new filtered image. 


## Future Enhancements

- [ ] Command line flags which allows you to chose the color for which you filter
- [ ] Support for other BMP files (like 32bit) or other file types (JPEG, PNG, etc)