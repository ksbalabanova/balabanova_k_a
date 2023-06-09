add_executable(tests
    ccr_test.cpp
)
target_link_libraries(tests ccr doctest::doctest ${OpenCV_LIBS})
add_test(NAME tests COMMAND tests)
