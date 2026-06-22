cmake_minimum_required(VERSION 3.23)
project(QuickINI)
set(PROJECT_NAME "QuickINI" STRING)

# Setting up libs
add_library(quickini)
target_sources(quickini
  PRIVATE
    src/parser.c

  PUBLIC
    FILE_SET quickini_headers
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/parser.h
)

# TEST EXE HERE
add_executable(libtest tests/deployment_tests/test.c)
target_link_libraries(libtest PRIVATE quickini)

# Read version from VERSION file
file(READ "${CMAKE_SOURCE_DIR}/VERSION" PROJECT_VERSION_RAW)
string(STRIP "${PROJECT_VERSION_RAW}" PROJECT_VERSION)

# Git commit hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Git branch
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Dirty flag
execute_process(
    COMMAND git diff --quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_DIRTY_RESULT
)
if(GIT_DIRTY_RESULT EQUAL 0)
    set(GIT_DIRTY 0)
else()
    set(GIT_DIRTY 1)
endif()

# Build date
string(TIMESTAMP BUILD_DATE "%Y-%m-%d")

# Generate version.h
configure_file(
    ${CMAKE_SOURCE_DIR}/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
    @ONLY
)

include_directories(${CMAKE_BINARY_DIR}/generated)