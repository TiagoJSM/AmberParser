cmake_minimum_required(VERSION 3.0.0)
project(AmberParser VERSION 0.1.0)

include(CTest)
enable_testing()

#include_directories("C:/Program Files/LLVM/include")

#add_subdirectory(Submodules/cppast)

file(GLOB HelpersSrc
    "Helpers/*.cpp"
)

file(GLOB DescriptorsSrc
    "ParsingData/BaseDescriptor.cpp"
	"ParsingData/ClassDescriptor.cpp"
	"ParsingData/FieldDescriptor.cpp"
	"ParsingData/NamespaceDescriptor.cpp"
)

configure_file("header.hpp" "header.hpp" COPYONLY)
configure_file("C:/Program Files/LLVM/bin/libclang.dll" "libclang.dll" COPYONLY)

#add_library(libclang STATIC IMPORTED) # or STATIC instead of SHARED
#set_target_properties(libclang PROPERTIES
#  IMPORTED_LOCATION "C:/Program Files/LLVM/lib/libclang.lib"
#  INTERFACE_INCLUDE_DIRECTORIES "C:/Program Files/LLVM/include"
#)

add_executable(AmberParser main.cpp Parser/Parser.cpp ${HelpersSrc} ${DescriptorsSrc} "ParsingData/TranslationUnitDescriptor.cpp" "ParsingData/StructDescriptor.hpp" "ParsingData/StructDescriptor.cpp")

#target_link_libraries(AmberParser "C:/Program Files/LLVM/lib")
#target_link_libraries(AmberParser libclang)
target_include_directories(
	AmberParser PUBLIC
	"C:/Program Files/LLVM/include")

target_link_libraries(
	AmberParser 
	"C:/Program Files/LLVM/lib/libclang.lib")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
