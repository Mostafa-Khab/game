#version 450

uniform vec3 lightColor;

in vec4 v_col;

out vec4 fragColor;

void main()
{
  fragColor = vec4(lightColor, 1.0);
}
