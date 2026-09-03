add_executable(basic_window basic_window/main.cpp)
target_link_libraries(basic_window PRIVATE endergfx::endergfx)

add_executable(rotating_cube rotating_cube/main.cpp)
target_link_libraries(rotating_cube PRIVATE endergfx::endergfx)

add_executable(model_loading model_loading/main.cpp)
target_link_libraries(model_loading PRIVATE endergfx::endergfx)

add_custom_command(TARGET model_loading POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/assets
          $<TARGET_FILE_DIR:model_loading>/assets
  COMMENT "Copying assets for model_loading"
)
