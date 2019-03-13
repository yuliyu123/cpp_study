# tests report output file name
set(GTEST_OUTPUT_XML ut.xml)

# pkg_check_modules(GTEST REQUIRED gtest)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    "${PROJECT_SOURCE_DIR}/test/mocks"
    "${PROJECT_SOURCE_DIR}/test/ut"
)

# dummy target to collect UT executables
add_custom_target(ut)

set(common_files
    ${PROJECT_SOURCE_DIR}/test/TestMain.cpp
)

# set(test_cases
#     # TinerTest.cc
# )

add_subdirectory(${PROJECT_SOURCE_DIR}/test/ut)

add_custom_target(ut-run
    COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_VERBOSE_FLAG} --output-on-failure -L "UT" -R "${TEST_CASE}"
    DEPENDS ut
)
