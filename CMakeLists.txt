cmake_minimum_required(VERSION 3.23)
project(QuickINI)

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

add_executable(libtest tests/test.c)
target_link_libraries(libtest PRIVATE quickini)

execute_process(
    COMMAND git describe --tags --abbrev=0
    OUTPUT_VARIABLE GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
    ${CMAKE_SOURCE_DIR}/config.h.in
    ${CMAKE_BINARY_DIR}/config.h
    @ONLY
)