add_library(srgb srgb.cpp include/srgb/srgb.hpp)
set_property(TARGET srgb PROPERTY CXX_STANDARD 20)
target_include_directories(srgb PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
install(TARGETS srgb DESTINATION lib)
install(FILES include/srgb/srgb.hpp DESTINATION include/srgb)
