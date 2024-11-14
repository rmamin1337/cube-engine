<div align="center">
  <br>
  <h1>🌱 CubeEngine 🌱</h1>
  <strong>Clear And Fast Cube Game Engine in C++ with OpenGL.</strong>
</div>
<br>
<p align="center">
  <a href="https://github.com/rmamin1337/cube-engine/actions/workflows/ci.yml">
    <img src="https://github.com/rmamin1337/cube-engine/actions/workflows/ci.yml/badge.svg" alt="Build Status">
  </a>

[//]: # (  <a href="https://github.com/rmamin1337/cube-engine/actions/workflows/cd.yml">)

[//]: # (    <img src="https://github.com/rmamin1337/cube-engine/actions/workflows/cd.yml/badge.svg" alt="Build Status">)

[//]: # (  </a>)
  <img src="https://img.shields.io/github/commit-activity/w/rmamin1337/cube-engine" alt="GitHub commit activity">
  <a href="https://github.com/rmamin1337/cube-engine/issues?q=is%3Aissue+is%3Aopen+label%3A%22ready+for+dev%22">
    <img src="https://img.shields.io/github/issues/rmamin1337/cube-engine/ready for dev" alt="GitHub issues ready for dev">
  </a>
  <a href="https://gitpod.io/#https://github.com/rmamin1337/cube-engine">
    <img src="https://img.shields.io/badge/setup-automated-blue?logo=gitpod" alt="GitPod badge">
  </a>
</p>


## What is CubeEngine?
CubeEngine is an open source game engine.

## Table of Contents
- [What is CubeEngine](#what-is-CubeEngine)
- [Table of Contents](#table-of-contents)
- [Documentation](#documentation)
- [Releases](#releases)
- [Getting Started](#getting-started)
    - [Build on Windows](#Build-on-Windows)
    - [Build on MacOS](#Build-on-MacOS)
    - [Build on Linux](#Build-on-Linux)
    - [Build with CMake](#Build-with-CMake)

## Documentation
- [Documentation](https://github.com/rmamin1337/cube-engine/blob/release-0.1/doc/en/main-page.md) | [Документация](https://github.com/rmamin1337/cube-engine/blob/release-0.1/doc/ru/main-page.md)

## Releases
- [Releases](https://github.com/rmamin1337/cube-engine/releases/latest) | [Релизы](https://github.com/rmamin1337/cube-engine/releases/latest)

## Getting Started

## Build on Windows
>[!NOTE]
> Requirement:
>
> vcpkg, CMake

```sh
git clone --recursive https://github.com/rmamin1337/cube-engine.git
cd cube-engine
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCUBEENGINE_BUILD_WINDOWS_VCPKG=ON ..
del CMakeCache.txt
rmdir /s /q CMakeFiles
cmake -DCMAKE_BUILD_TYPE=Release -DCUBEENGINE_BUILD_WINDOWS_VCPKG=ON ..
cmake --build . --config Release
```

> [!TIP]
> You can use ```rm CMakeCache.txt``` and ```rm -rf CMakeFiles``` while using Git Bash

> [!WARNING]
> If you have issues during the vcpkg integration, try navigate to ```vcpkg\downloads```
> and extract PowerShell-[version]-win-x86 to ```vcpkg\downloads\tools``` as powershell-core-[version]-windows.
> Then rerun ```cmake -DCMAKE_BUILD_TYPE=Release -DCUBEENGINE_BUILD_WINDOWS_VCPKG=ON ..```

## Build on MacOS
### Install libraries

```sh
brew install yaml-cpp pkg-config glfw3 glew glm libpng libvorbis lua luajit openal-soft skypjack/entt/entt
```

> [!TIP]
> If homebrew for some reason could not install the necessary packages:
> ```lua luajit openal-soft```, then download, install and compile them manually
> (Lua, LuaJIT and OpenAL).

## Build on Linux
### Install libraries
#### Install EnTT

```sh
git clone https://github.com/skypjack/entt.git
cd entt/build
cmake -DCMAKE_BUILD_TYPE=Release ..
sudo make install
```

> [!WARNING]
> If you are using ALT Linux, you should not use this EnTT installation method

#### ALT Linux-based distro

```sh
su -
apt-get install yaml-cpp entt-devel libglfw3-devel libGLEW-devel libglm-devel libpng-devel libvorbis-devel libopenal-devel libluajit-devel libstdc++13-devel-static
```

#### Debian-based distro

```sh
sudo apt install yaml-cpp libglfw3-dev libglfw3 libglew-dev libglm-dev libpng-dev libopenal-dev libluajit-5.1-dev libvorbis-dev
```

> [!TIP]
> CMake missing LUA_INCLUDE_DIR and LUA_LIBRARIES fix:
>
> ```sh
> sudo ln -s /usr/lib/x86_64-linux-gnu/libluajit-5.1.a /usr/lib/x86_64-linux-gnu/liblua5.1.a
> sudo ln -s /usr/include/luajit-2.1 /usr/include/lua
> ```

#### RHEL-based distro

```sh
sudo dnf install yaml-cpp glfw-devel glfw glew-devel glm-devel libpng-devel libvorbis-devel openal-devel luajit-devel
```

#### Arch-based distro

If you use X11

```sh
sudo pacman -S yaml-cpp glfw-x11 glew glm libpng libvorbis openal luajit
```

If you use Wayland

```sh
sudo pacman -S yaml-cpp glfw-wayland glew glm libpng libvorbis openal luajit
```

### Build with CMake
```sh
git clone --recursive https://github.com/rmamin1337/cube-engine.git
cd cube-engine
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```