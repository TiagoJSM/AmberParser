cmake_minimum_required (VERSION 3.16)
project(AmberParserTool C CXX)

add_executable (AmberParserTool "src/main.cpp")

target_include_directories(AmberParserTool PUBLIC ${AmberParser_INCLUDE_DIRS})

target_link_libraries(AmberParserTool AmberParser)

add_custom_command(TARGET AmberParserTool PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/AmberParserTool/TestFiles/ $<TARGET_FILE_DIR:AmberParserTool>/TestFiles)