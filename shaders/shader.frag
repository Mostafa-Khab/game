#version 450

uniform sampler2D u_tex0;
uniform sampler2D u_tex1;

in vec4 v_col;
in vec2 v_uv;
in vec3 v_normal;

in vec3 v_pos;
in vec3 v_lightPos;

out vec4 fragColor;

void main()
{
  vec3 ambient = vec3(1.0) * 0.1; //light color * ambientStrengh

  vec3 norm    = normalize(v_normal);
  vec3 lightDir= normalize(v_lightPos - v_pos);

  float diff   = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * vec3(1.0); // lightColor = vec3(1.0)

  fragColor    = vec4(ambient + diffuse, 1.0) * v_col * mix(texture(u_tex0, v_uv), texture(u_tex1, v_uv), 0.5); 
}
