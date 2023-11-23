cmake_minimum_required(VERSION 3.20)

project(uge LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(filter)
include(folder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Build each of our projects into a dll if we are in debug mode
if($<CONFIG:DEBUG>)
    set(UGE_DLL ON ENV{UGE_DLL})
else()
    set(UGE_DLL OFF ENV{UGE_DLL})
endif()

add_definitions(-DUNICODE -D_UNICODE)
add_compile_definitions($<$<CONFIG:Debug>:UGE_DEBUG> $<$<CONFIG:Debug>:UGE_DLL>) # Add UGE_DEBUG if the build configuration is set in Debug

add_subdirectory(src)