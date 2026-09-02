add_executable(basic_window basic_window/main.cpp)
target_link_libraries(basic_window PRIVATE endergfx::endergfx)

add_executable(rotating_cube rotating_cube/main.cpp)
target_link_libraries(rotating_cube PRIVATE endergfx::endergfx)
