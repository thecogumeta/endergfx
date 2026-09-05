$input v_normal, v_color0

#include <bgfx_shader.sh>

uniform vec4 u_lightDir;
uniform vec4 u_lightColor;

void main() {
  vec3 normal = normalize(v_normal);
  vec3 lightDir = normalize(u_lightDir.xyz);

  float diffuse = max(dot(normal, lightDir), 0.0);
  float ambient = u_lightColor.a;
  float intensity = ambient + diffuse * (1.0 - ambient);

  vec3 litColor = v_color0.rgb * u_lightColor.rgb * intensity;
  gl_FragColor = vec4(litColor, v_color0.a);
}
