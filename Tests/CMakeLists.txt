cmake_minimum_required (VERSION 3.16)

project(AmberParserTests C CXX)

# TODO: Add tests and install targets if needed.

#set(SubmodulesPath ${CMAKE_SOURCE_DIR}/Submodules)
#set(Catch2Path ${SubmodulesPath}/catch2)

add_executable (AmberParserTests "src/ParserOutputTests.cpp" "src/TestsMain.cpp")

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(AmberParserTests Catch2::Catch2)
