cmake_minimum_required (VERSION 3.16)
project(AmberParserTests C CXX)

add_executable (AmberParserTests "src/ParserOutputTests.cpp" "src/TestsMain.cpp" "TestFiles/NothingToGenerate.hpp")

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

target_include_directories(AmberParserTests PUBLIC ${AmberParser_INCLUDE_DIRS})
target_link_libraries(AmberParserTests Catch2::Catch2 AmberParser)

add_custom_command(TARGET AmberParserTests PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/AmberParserTests/TestFiles/ $<TARGET_FILE_DIR:AmberParserTests>/TestFiles)

add_custom_command(TARGET AmberParserTests PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/AmberParserTests/ResultFiles/ $<TARGET_FILE_DIR:AmberParserTests>/ResultFiles)