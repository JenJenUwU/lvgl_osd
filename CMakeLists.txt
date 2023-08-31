cmake_minimum_required(VERSION 3.16)
include(FetchContent)
project(lvgl_osd
    VERSION 0.1.0
    DESCRIPTION "OSD by LVGL"
    LANGUAGES CXX C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/include_submodules.cmake)
add_submodules_in_directory(submodules)

add_subdirectory(lvgl_osd)
# Specify path to own LVGL config header
set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl_osd/src/lv_conf.h
    CACHE STRING "" FORCE)
set(LV_DRV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl_osd/src/lv_drv_conf.h
    CACHE STRING "" FORCE)
# Fetch LVGL from GitHub
FetchContent_Declare(
    lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl.git
    GIT_TAG release/v8.2
)
FetchContent_MakeAvailable(lvgl)
FetchContent_Declare(
    lv_drivers
    GIT_REPOSITORY https://github.com/lvgl/lv_drivers.git
    GIT_TAG release/v8.2
)
FetchContent_MakeAvailable(lv_drivers)
# The target "lvgl_osd" depends on LVGL
target_link_libraries(lvgl PUBLIC freetype)
target_link_libraries(lvgl_osd PRIVATE lvgl::lvgl lvgl::drivers freetype)