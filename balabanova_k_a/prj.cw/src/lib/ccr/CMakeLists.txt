add_library(ccr ccr.cpp include/ccr/ccr.hpp)
set_property(TARGET ccr PROPERTY CXX_STANDARD 20)
target_include_directories(ccr PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
install(TARGETS ccr DESTINATION lib)
install(FILES include/ccr/ccr.hpp DESTINATION include/ccr)
