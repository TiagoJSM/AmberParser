cmake_minimum_required(VERSION 3.0.0)
project(AmberParser VERSION 0.1.0)

include(CTest)
enable_testing()

#include_directories("C:/Program Files/LLVM/include")

#add_subdirectory(Submodules/cppast)

file(GLOB HelpersSrc
    "Helpers/*.cpp"
)

configure_file("header.hpp" "header.hpp" COPYONLY)

add_library(libclang STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(libclang PROPERTIES
  IMPORTED_LOCATION "C:/Program Files/LLVM/lib/libclang.lib"
  INTERFACE_INCLUDE_DIRECTORIES "C:/Program Files/LLVM/include"
)

add_executable(AmberParser main.cpp Parser/Parser.cpp ${HelpersSrc})

#target_link_libraries(AmberParser "C:/Program Files/LLVM/lib")
target_link_libraries(AmberParser libclang)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
