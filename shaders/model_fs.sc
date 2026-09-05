$input v_normal, v_texcoord0, v_color0

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);
uniform vec4 u_lightDir;
uniform vec4 u_lightColor;

void main() {
  vec3 normal = normalize(v_normal);
  vec3 lightDir = normalize(u_lightDir.xyz);

  float diffuse = max(dot(normal, lightDir), 0.0);
  float ambient = u_lightColor.a;
  float intensity = ambient + diffuse * (1.0 - ambient);

  vec4 texColor = texture2D(s_texColor, v_texcoord0);
  vec3 litColor = texColor.rgb * v_color0.rgb * u_lightColor.rgb * intensity;

  gl_FragColor = vec4(litColor, texColor.a * v_color0.a);
}
