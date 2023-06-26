cmake_minimum_required(VERSION 3.18)   

project(ccrlib_cw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(build_prefix)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(GNUInstallDirs)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-anon-enum-enum-conversion")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

if (DOXYGEN)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(CCN_DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(CCN_DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
        configure_file(${CCN_DOXYGEN_IN} ${CCN_DOXYGEN_OUT})
        add_custom_target(ccrlib_doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${CCN_DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ccrlib_doc
            DESTINATION ./bin)
    else ()
        message(STATUS "Could not find Doxygen")
    endif ()
endif ()


add_subdirectory(src)
