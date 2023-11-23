file (GLOB_RECURSE coreSystemSrc CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h *.hpp *.inl)

if (UGE_DLL)
    add_library(coreSystem SHARED ${coreSystemSrc})
else()
    add_library(coreSystem STATIC ${coreSystemSrc})
endif()

target_compile_definitions(coreSystem PRIVATE
    -DUGE_CORESYSTEM_EXPORT
)

target_link_libraries(coreSystem Dbghelp.lib
)

target_include_directories(coreSystem
PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_precompile_headers (coreSystem
PRIVATE
  build.h
)

set_target_properties(coreSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<1:>"
    OUTPUT_NAME "${OUTPUT_NAME}"
)
