#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

in vec3 a_pos;
in vec4 a_col;
in vec2 a_uv;
in vec3 a_normal;

out vec4 v_col;
out vec2 v_uv;
out vec3 v_normal;

out vec3 v_pos;
out vec3 v_lightPos;

void main()
{
  gl_Position = projection * view * model * vec4(a_pos, 1.0);
  v_col       = a_col;
  v_uv        = a_uv;
  v_normal    = vec3(projection * model * vec4(a_normal, 1.0));
  v_pos       = vec3(projection * model * vec4(a_pos, 1.0));//vec3(model * vec4(a_pos, 1.0));
  v_lightPos  = vec3(projection * model * vec4(lightPos, 1.0));
}
