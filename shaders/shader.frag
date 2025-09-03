#version 450

uniform sampler2D u_tex0;
uniform sampler2D u_tex1;

in vec4 v_col;
in vec2 v_uv;

out vec4 fragColor;

void main()
{
  fragColor = v_col * mix(texture(u_tex0, v_uv), texture(u_tex1, v_uv), 0.5); 
}
