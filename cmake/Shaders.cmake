set(ENDERGFX_SHADER_GEN_DIR ${CMAKE_BINARY_DIR}/generated/shaders)

bgfx_compile_shaders(
  TYPE VERTEX
  SHADERS ${CMAKE_SOURCE_DIR}/shaders/model.vs.sc
  VARYING_DEF ${CMAKE_SOURCE_DIR}/shaders/varying.def.sc
  OUTPUT_DIR ${ENDERGFX_SHADER_GEN_DIR}
  AS_HEADERS
)

bgfx_compile_shaders(
  TYPE FRAGMENT
  SHADERS ${CMAKE_SOURCE_DIR}/shaders/model.fs.sc
  VARYING_DEF ${CMAKE_SOURCE_DIR}/shaders/varying.def.sc
  OUTPUT_DIR ${ENDERGFX_SHADER_GEN_DIR}
  AS_HEADERS
)
