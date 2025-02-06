# Set the cmake minimum version
cmake_minimum_required(VERSION 3.5)

# Define the project name
project(market)

# Generate symbols for IDE indexer
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to C11
set(CMAKE_C_STANDARD 11)

# Set source files
file(GLOB SOURCES "src/*.c")

# Set include directories
include_directories("include")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add compilation flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
