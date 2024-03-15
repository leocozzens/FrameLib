function(GetRemote)
    cmake_parse_arguments(REMOTE "" "NAME;VERSION;PARENT_DIR;REPO;TAG;CMAKE_DIR" "" ${ARGN})

    include(FetchContent)
    set(REMOTE_DESTINATION ${REMOTE_PARENT_DIR}/${REMOTE_NAME})

    set(REMOTE_NAME extern_${REMOTE_NAME})
    if(REMOTE_CMAKE_DIR)
    FetchContent_Declare(
        ${REMOTE_NAME}
        SOURCE_DIR          ${REMOTE_DESTINATION}
        SOURCE_SUBDIR       ${REMOTE_CMAKE_DIR}
        GIT_REPOSITORY      ${REMOTE_REPO}
        GIT_TAG             ${REMOTE_TAG}
        GIT_SHALLOW		    TRUE
        FIND_PACKAGE_ARGS   ${REMOTE_VERSION}
    )
    else()
    FetchContent_Declare(
        ${REMOTE_NAME}
        SOURCE_DIR          ${REMOTE_DESTINATION}
        GIT_REPOSITORY      ${REMOTE_REPO}
        GIT_TAG             ${REMOTE_TAG}
        GIT_SHALLOW		    TRUE
        FIND_PACKAGE_ARGS   ${REMOTE_VERSION}
    )
    endif()

    FetchContent_MakeAvailable(${REMOTE_NAME})
    set("${REMOTE_NAME}_LOCATION" ${REMOTE_DESTINATION} PARENT_SCOPE)
endfunction()

function(GetRepo)
    cmake_parse_arguments(REPO "" "NAME;VERSION;PATH;INCLUDES;SOURCES" "" ${ARGN})
    if(NOT REPO_PATH)
        set(REPO_PATH ${CMAKE_SOURCE_DIR}/external)
    endif()

    message(STATUS "REPO PATH: ${REPO_PATH}")
    set(REPO_DESTINATION ${REPO_PATH}/${REPO_NAME}/)
    list(TRANSFORM REPO_SOURCES PREPEND ${REPO_DESTINATION})

    add_library(
        ${REPO_NAME} STATIC
        ${REPO_SOURCES}
     )
    list(TRANSFORM REPO_INCLUDES PREPEND ${REPO_DESTINATION})
    target_include_directories(
        ${REPO_NAME} PUBLIC
        ${REPO_INCLUDES}
    )

    if(REPO_VERSION)
        set_target_properties(
            ${REPO_NAME} PROPERTIES
            VERSION ${REPO_VERSION}
        )
    endif()
endfunction()