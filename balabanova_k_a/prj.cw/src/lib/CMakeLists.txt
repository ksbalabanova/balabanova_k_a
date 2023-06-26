set (CCR_LIBRARY ccrlibrary)

file (GLOB SRC 
        ccr/ccr.cpp
        srgb/srgb.cpp)

add_library(${CCR_LIBRARY} ${SRC})

install(TARGETS ${CCR_LIBRARY}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY ccr/include/ccr
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY srgb/include/srgb
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

configure_file(../../cmake/ccrlibraryConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/ccrlibraryConfig.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ccrlibraryConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ccrlibrary)
        
target_link_libraries(${CCR_LIBRARY} PUBLIC ${OpenCV_LIBS})
