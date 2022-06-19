cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(linux.toolchain)

project(ElfStudy)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

find_package(spdlog REQUIRED)

include_directories(${LLVM_INCLUDE_DIRS} include)
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Now build our tools
add_executable(ElfStudy 
    src/main.cc
    src/elf.cc
    src/elf_header.cc
    src/program_header.cc
    src/section_header.cc
    src/string_tab.cc
    src/symbol_tab.cc
)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(ElfStudy PRIVATE 
    ${llvm_libs} 
    spdlog::spdlog_header_only
)
