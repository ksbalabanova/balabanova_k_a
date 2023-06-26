add_executable(ccrexe main.cpp )

# Link libraries
target_link_libraries(ccrexe PRIVATE ccrlibrary)
target_link_libraries(ccrexe PRIVATE ${OpenCV_LIBS})

target_include_directories(ccrexe PRIVATE
    ${CMAKE_SOURCE_DIR}/prj.cw/src/lib/ccr/include
    ${CMAKE_SOURCE_DIR}/prj.cw/src/lib/srgb/include
)

#Define a constant variable for main.cpp code
target_compile_definitions(ccrexe PRIVATE INSTALL_PATH="${CMAKE_INSTALL_PREFIX}/bin")

install(TARGETS ccrexe RUNTIME DESTINATION ./bin
        COMPONENT Runtime)

#Install all dll dependencies along with executable
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/photo_test DESTINATION ./bin)