add_executable(ccrlib
    main.cpp
)

# Link the executable with YourLibraryName and OpenCV
target_compile_definitions(ccrlib PRIVATE INSTALL_PATH="${CMAKE_INSTALL_PREFIX}/bin")
target_link_libraries(ccrlib PRIVATE srgb ccr)
target_link_libraries(ccrlib PRIVATE ${OpenCV_LIBS})

install(TARGETS ccrlib DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/photo_test DESTINATION ./bin)
