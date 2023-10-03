cmake_minimum_required(VERSION 3.20)

project(uge LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(filter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build each of our projects into a dll instead of linking it
if($<CONFIG:DEBUG>)
    set(UGE_DLL ON)
else()
    set(UGE_DLL OFF)
endif()

add_definitions(-DUNICODE -D_UNICODE)
add_compile_definitions($<$<CONFIG:Debug>:UGE_DEBUG>) # Add UGE_DEBUG if the build configuration is set in Debug

add_subdirectory(src)