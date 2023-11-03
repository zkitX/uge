file (GLOB_RECURSE coreMathSrc CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.hpp *.inl)

add_library(coreMath STATIC
    ${coreMathSrc}
)

target_include_directories(coreMath
PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_precompile_headers (coreMath
PRIVATE
  build.h
)

set_target_properties(coreMath PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<1:>"
    OUTPUT_NAME "${OUTPUT_NAME}"
)
