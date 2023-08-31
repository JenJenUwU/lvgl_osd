set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools /toolchains/gcc-sigmastar-9.1.0-2020.07-x86_64_arm-linux-gnueabihf/bin)
set(CMAKE_C_COMPILER ${tools}/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/arm-linux-gnueabihf-g++)
set(CMAKE_STRIP ${tools}/arm-linux-gnueabihf-strip)

set(CMAKE_FIND_ROOT_PATH /toolchains/gcc-sigmastar-9.1.0-2020.07-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
