
cmake_minimum_required(VERSION 3.10)
project(MyDriver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Xerces-C++ library
find_library(XERCES_LIB xerces-c PATHS /usr/local/lib)

# Specify include directory (if required)
include_directories(/usr/local/include)

# Run XSD tool to generate C++ files from hello.xsd
add_custom_command(
    OUTPUT basicihp.hxx basicihp.cxx
    COMMAND xsd cxx-tree ../basicihp.xsd
    DEPENDS basicihp.xsd
    COMMENT "Generating C++ files from hello.xsd"
)

# Define a custom target to generate the schema files
add_custom_target(generate_xsd
    DEPENDS basicihp.hxx basicihp.cxx
)

# Define source files
set(SOURCES
    driver.cxx
    basicihp.cxx
)

# Add the executable
add_executable(driver ${SOURCES})

# Ensure `driver` is built after the XSD-generated files are created
add_dependencies(driver generate_xsd)

# Link Xerces-C++
target_link_libraries(driver ${XERCES_LIB})
