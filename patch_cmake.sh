#! /bin/sh

ROOT=$PWD

cd /usr/share/cmake-2.8/Modules/
patch < $ROOT/cmake_patch_linaro.diff

cd /usr/share/cmake-2.8/Modules/Platform/
patch < $ROOT/cmake_patch_arm_none_eabi.diff
