cmake_minimum_required(VERSION 3.25.1)

set(EX_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
set(GLAD_VERSION 2.0.5)
GetRemote(
    NAME        glad
    VERSION     ${GLAD_VERSION}
    REPO        https://github.com/Dav1dde/glad
    TAG         "v${GLAD_VERSION}"
    PARENT_DIR  ${EX_LIB_DIR}
    CMAKE_DIR   cmake
)

glad_add_library(glad_core STATIC API gl:core=4.6)

CompileExample(
    NAME 001_window
    # DEPENDENCIES OpenGL::GL glad_core
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include
    SRCS main.c
)