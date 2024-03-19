# CMake version settings
cmake_minimum_required(VERSION 3.25.1)
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.18)
    cmake_policy(SET CMP0135 NEW)
endif()
# Project data
project(FrameLib VERSION 0.1.0 LANGUAGES C)

# Platform options
set(API_LIST Win32 Headless Cocoa XCB XLib)
set(FLIB_API AUTO CACHE STRING "Underlying platform API for ${PROJECT_NAME} to use")

# Platform detection
# TODO: Implement platform detection
if(${FLIB_API} STREQUAL AUTO)
    set(FLIB_API Win32)
endif()

# Platform validation
set(VALID_API FALSE)
foreach(API ${API_LIST})
    if(${API} STREQUAL ${FLIB_API})
        set(VALID_API TRUE)
        break()
    endif()
endforeach()

if(NOT ${VALID_API})
    message(FATAL_ERROR "${FLIB_API} is not a recognized FrameLib platform API. Please select from the following: ${API_LIST}.")
endif()

# Build options
option(FLIB_BUILD_TESTS "Enable tests" OFF)
option(FLIB_BUILD_EXAMPLES "Build example executables" OFF)

# General build settings
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -O0")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

# Build type detection
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# List sources
set(COMMON_SRCS "")
list(TRANSFORM COMMON_SRCS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/)

file(GLOB_RECURSE API_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/${FLIB_API}/*.c)
set(FLIB_SRCS ${COMMON_SRCS} ${API_SRCS})

# Dependencies
set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/cmake/utils)
include(${SCRIPT_DIR}/remotes.cmake)
include(${SCRIPT_DIR}/compile_tools.cmake)

set(DEPENDENCIES "")

# Set header locations
set(
    INTERNAL_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/${FLIB_API}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/include
)
set(
    INTERFACE_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} STATIC ${FLIB_SRCS})
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${INTERNAL_INCLUDES}
    PUBLIC
    ${INTERFACE_INCLUDES}
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    ${DEPENDENCIES}
)

if(${FLIB_BUILD_TESTS})
    message(STATUS "Tests are enabled for ${PROJECT_NAME}")
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Tests are disabled for ${PROJECT_NAME}")
endif()

if(${FLIB_BUILD_EXAMPLES})
    message(STATUS "Example executables are enabled for ${PROJECT_NAME}")
    add_subdirectory(examples)
else()
    message(STATUS "Example executables are disabled for ${PROJECT_NAME}")
endif()