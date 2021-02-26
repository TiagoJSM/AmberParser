cmake_minimum_required(VERSION 3.0.0)
project(AmberParser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

#include_directories("C:/Program Files/LLVM/include")

#add_subdirectory(Submodules/cppast)

file(GLOB HelpersSrc
    "Helpers/*.cpp"
)

file(GLOB DescriptorsSrc
    "ParsingData/BaseDescriptor.cpp"
	"ParsingData/FieldDescriptor.cpp"
	"ParsingData/NamespaceDescriptor.cpp"
)

configure_file("$ENV{LibClangPath}/libclang.dll" "libclang.dll" COPYONLY)

add_executable(AmberParser main.cpp Parser/Parser.cpp ${HelpersSrc} ${DescriptorsSrc} "ParsingData/TranslationUnitDescriptor.cpp" "BuildGeneration/CMakeListsTemplate.hpp" "BuildGeneration/TypeRegistration.cpp" "BuildGeneration/Attributes.hpp" "BuildGeneration/RegistrationWritter.hpp" "BuildGeneration/RegistrationWritter.cpp" "TestFiles/BaseClass.hpp" "ParsingData/CompoundDescriptor.hpp" "ParsingData/CompoundDescriptor.cpp" "TestFiles/TemplateBase.hpp" "BuildGeneration/RegistrationFile.hpp" "BuildGeneration/RegistrationFile.cpp")

#target_link_libraries(AmberParser "C:/Program Files/LLVM/lib")
#target_link_libraries(AmberParser libclang)
target_include_directories(
	AmberParser PUBLIC
	"C:/Program Files/LLVM/include")

target_link_libraries(
	AmberParser 
	"C:/Program Files/LLVM/lib/libclang.lib")


add_custom_command(TARGET AmberParser PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/TestFiles/ $<TARGET_FILE_DIR:AmberParser>/TestFiles)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
