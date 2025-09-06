#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 a_pos;
in vec4 a_col;

out vec4 v_col;

void main()
{
  gl_Position = projection * view * model * vec4(a_pos, 1.0);
  v_col       = a_col;
}
