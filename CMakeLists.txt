cmake_minimum_required(VERSION 3.0.0)
project(AmberParser VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(Submodules/cppast)

add_subdirectory(Submodules/cppast)

add_executable(AmberParser main.cpp)

target_link_libraries(AmberParser Submodules/cppast)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
