cmake_minimum_required(VERSION 3.16)


add_executable(${PROJECT_NAME})

option(SDK_DIR "PVM SDK root dir" "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_osd_menu_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_osd_indev.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_menu_obj.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cb_output/btn_cb_output.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cb_output/dropdown_cb_output.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cb_output/slider_cb_output.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cb_output/switch_cb_output.c
)

add_custom_command(
    TARGET "${PROJECT_NAME}" POST_BUILD
    DEPENDS "${PROJECT_NAME}"
    COMMAND $<$<CONFIG:minsizerel>:${CMAKE_STRIP}>
    ARGS --strip-all $<TARGET_FILE:${PROJECT_NAME}>
)
