cmake_minimum_required (VERSION 3.16)
project(AmberParser C CXX)

file(GLOB HelpersSrc
    "Helpers/*.cpp"
)

file(GLOB DescriptorsSrc
    "ParsingData/BaseDescriptor.cpp"
	"ParsingData/FieldDescriptor.cpp"
	"ParsingData/NamespaceDescriptor.cpp"
)

configure_file("$ENV{LibClangPath}/bin/libclang.dll" "libclang.dll" COPYONLY)

add_library(AmberParser main.cpp Parser/Parser.cpp ${HelpersSrc} ${DescriptorsSrc} "ParsingData/TranslationUnitDescriptor.cpp" "BuildGeneration/CMakeListsTemplate.hpp" "BuildGeneration/TypeRegistration.cpp" "BuildGeneration/Attributes.hpp" "BuildGeneration/RegistrationWrittable.hpp" "BuildGeneration/RegistrationWrittable.cpp" "TestFiles/BaseClass.hpp" "ParsingData/CompoundDescriptor.hpp" "ParsingData/CompoundDescriptor.cpp" "TestFiles/TemplateBase.hpp" "BuildGeneration/RegistrationFile.hpp" "BuildGeneration/RegistrationFile.cpp")

target_include_directories(
	AmberParser PUBLIC
	"$ENV{LibClangPath}/include")

target_link_libraries(
	AmberParser 
	"$ENV{LibClangPath}/lib/libclang.lib")


add_custom_command(TARGET AmberParser PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/AmberParser/TestFiles/ $<TARGET_FILE_DIR:AmberParser>/TestFiles)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
