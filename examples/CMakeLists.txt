function(endergfx_add_example name)
  add_executable(${name} ${name}/main.cpp)
  target_link_libraries(${name} PRIVATE endergfx::endergfx)

  add_custom_command(TARGET ${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${name}>/assets
    COMMENT "Copying assets for ${name}"
  )
endfunction()

endergfx_add_example(basic_window)
endergfx_add_example(rotating_cube)
endergfx_add_example(model_loading)
endergfx_add_example(textured_cube)
