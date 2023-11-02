file (GLOB_RECURSE testGameSrc CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.hpp *.inl)

add_executable(testGame ${testGameSrc})

target_include_directories(testGame
PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(testGame PUBLIC coreSystem Dbghelp.lib)

target_precompile_headers (testGame
PRIVATE
  build.h
)

set_target_properties(testGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<1:>"
    OUTPUT_NAME "${OUTPUT_NAME}"
)
