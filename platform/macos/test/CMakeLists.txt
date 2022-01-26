
set(GTEST_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
set(GMOCK_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/googletest-src/googlemock/include)
include_directories("${GTEST_INCLUDE_DIRS}" "${GMOCK_INCLUDE_DIRS}")

add_subdirectory(cpp)

