<img align="left" src="doc/openrt_logo.png" width="250px">

# Open Source Ray Tracing Library

[![License](https://img.shields.io/badge/license-BSD%203--Clause-green.svg)](License.txt)
[![CodeFactor](https://www.codefactor.io/repository/github/project-10/openrt/badge)](https://www.codefactor.io/repository/github/project-10/openrt)
[![Build status](https://ci.appveyor.com/api/projects/status/lpyxixb9utmwaur3?svg=true)](https://ci.appveyor.com/project/Creator/openrt)

OpenRT is a C++ ray-tracing library, which allows for synthesis of photo-realistic images. First of all, the library is developed for academic purposes: as an accompaniment to the computer graphics course and as a teaching aid for university students. Specifically, it includes the following features:
- **Distribution Ray Tracing**
- **Global Illumination**

OpenRT aims for a realistic simulation of [light transport](https://en.wikipedia.org/wiki/Computer_graphics_lighting), as compared to other rendering libraries, such as based on [rasterisation](https://en.wikipedia.org/wiki/Rasterisation), which focuses more on the realistic simulation of geometry. Effects such as reflections and shadows, which are difficult to simulate using other algorithms, are a natural result of the ray tracing algorithm. The computational independence of each ray makes our ray-tracing library amenable to a basic level of parallelisation. OpenRT is released under a BSD license and hence it is free for both academic and commercial use. The code is written entirely in C++ with using the [OpenCV](www.opencv.org) library. 

Check out the [project site](www.openrt.org) for all the details like
- Online documentation
- Installation guide
- Tutorials

Please join the [OpenRT-user Q&A forum](http://project-10.de/forum/viewforum.php?f=33) to ask questions and talk about methods and models. Framework development discussions and thorough bug reports are collected on [Issues](https://github.com/Project-10/OpenRT/issues).

## Installation
OpenRT is a cross-platform C++ library. The description here was tested on Windows 10 / Visual Studio 2019, macOS Catalina 10.15.6 / Xcode 11.4 and Ubuntu 18.04 / gcc 7.3.0. If you encounter errors after following the steps described below, feel free to contact us via our [User Q&A forum](http://project-10.de/forum/viewforum.php?f=33) or [Issues](https://github.com/Project-10/OpenRT/issues). We'll do our best to help you out.
OpenRT has only one dependency: it is based on [OpenCV](www.opencv.org) library. In order to use the OpenRT library, the OpenCV library should be also installed.

### Installing OpenCV
- Download the latest version of the OpenCV library from https://www.opencv.org/releases.html
- Build and install the library. You may follow the following guidance:
   - [Installation in Windows guide](https://docs.opencv.org/4.4.0/d3/d52/tutorial_windows_install.html) or
   - [Installation in Linux guide](https://docs.opencv.org/4.4.0/d7/d9f/tutorial_linux_install.html)

### Installing OpenRT
- Download either the latest stable OpenRT version from [Project X Research](https://research.project-10.de/openrt/#downloads) or fork the latest snapshot from our [GitHub repository](https://github.com/Project-10/OpenRT)
- Unpack it to your local folder (for example to disk **C:\\** for Windows or to **/Users/username/** for MacOS, so the library path will be **C:\OpenRT\\** or **/Users/username/OpenRT/**)

#### Installation in Windows and macOS
##### Building OpenRT from Source Using CMake GUI
In case you want to build the library (recommended), follow these instructions, otherwise - skip this step and proceed to [Using the Pre-built Libraries](#using-the-pre-built-libraries). This step also assumes that you have downloaded the sources of the OpenRT library.

- Download and install [CMake](https://cmake.org/download/) for your operating system
- Run **cmake-gui.exe** in Windows or **CMake.app** in MacOS
- In the _"Where is the source code"_ field choose the OpenRT source directory: **OpenRT**.
In the _"Where to build the binaries"_ field choose directory where Visual Studio or Xcode project files will be generated: _e.g._ **OpenRT/build**
- Press _Configure_ button and choose _Visual Studio_ for using 32-bit compiler, _Visual Studio Win64_ for using 64-bit compiler or Xcode as building environment
- Be sure that the _OpenCV_DIR_ is pointing to the OpenCV installation directory (_e.g._ **OpenCV/build/install** or **/usr/local/share/OpenCV**), where **OpenCVConfig.cmake** file is located
- (Optionally) you can change _CMAKE_INSTALL_PREFIX_ to the directory where the OpenRT binaries will be installed (_e.g._ to **OpenRT/build/install**)
- Press one more time _Configure_ and then Generate, so the IDE project files will be generated in the **OpenRT/build**
- Open the generated project by pressing the Open Project button or directly by opening file **OpenRT/build/OpenRT.sln** or **OpenRT/build/OpenRT.xcodeproj**
- Build **ALL_BUILD** and **INSTALL** projects first for Debug and then for Release configuration. That will copy OpenRT headers, binaries and demonstration applications to the install folder **OpenRT/build/install**
- Windows users may copy the OpenCV binaries into the install folder by executing script **/OpenRT/build/install/bin/copyOpenCVDLL.bat**
- (Optionally) you can copy the install folder with the ready-to-use OpenRT library (_e.g._ **OpenRT/build/install**) to any other folder

##### Using the Pre-built Libraries
This step assumes that you have downloaded OpenRT-package with the pre-build binaries. In such case the type and version of the downloaded binaries should correspond to your C++ compiler. If it is not, please return to the [Building OpenRT from Source Using CMake GUI](#building-openrt-from-source-using-cmake-gui) section and generate the binaries with your compiler. The content of the install folder (_e.g._ **OpenRT/build/install**) will correspond to the downloaded pre-build OpenRT package.

#### Installation in Linux
##### Building OpenRT from Source Using Terminal
For installing the OpenRT library for Ubuntu we assume that the OpenCV library was already installed ([Installing OpenCV](#installing-opencv)), thus GCC, CMake and Git are also installed. In order to download and install the latest version from master input the following commands in terminal:
```
cd ~/<my_working_directory>
git clone https://github.com/Project-10/OpenRT.git
cd OpenRT
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local
make
make install
make clean
```

![](./doc/cube_00.jpg)  
![](./doc/cube_10.jpg)
