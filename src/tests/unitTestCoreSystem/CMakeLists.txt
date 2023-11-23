add_executable(unitTestCoreSystem
    main.cpp
    tests/threadsTest.cpp
)

target_include_directories(unitTestCoreSystem
PRIVATE
    ${gtest_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(unitTestCoreSystem
    gtest
    coreSystem
)

include (GoogleTest)
gtest_discover_tests(unitTestCoreSystem)

