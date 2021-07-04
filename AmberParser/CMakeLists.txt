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

add_library(AmberParser Parser/Parser.cpp ${HelpersSrc} ${DescriptorsSrc} "ParsingData/TranslationUnitDescriptor.cpp" "BuildGeneration/CMakeListsTemplate.hpp" "BuildGeneration/TypeRegistration.cpp" "BuildGeneration/Attributes.hpp" "BuildGeneration/RegistrationWrittable.hpp" "BuildGeneration/RegistrationWrittable.cpp" "ParsingData/CompoundDescriptor.hpp" "ParsingData/CompoundDescriptor.cpp" "BuildGeneration/RegistrationFile.hpp" "BuildGeneration/RegistrationFile.cpp" "ParsingData/MethodDescriptor.hpp" "ParsingData/MethodDescriptor.cpp")

set(Submodules ${CMAKE_SOURCE_DIR}/Submodules)

target_include_directories(
	AmberParser PUBLIC
	"$ENV{LibClangPath}/include"
	${Submodules})

target_link_libraries(
	AmberParser 
	"$ENV{LibClangPath}/lib/libclang.lib")


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)