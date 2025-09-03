#version 450

in vec3 a_pos;
in vec4 a_col;

out vec4 v_col;

void main()
{
  gl_Position = vec4(a_pos, 1.0);
  v_col       = a_col;
}
