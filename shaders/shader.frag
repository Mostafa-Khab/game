#version 450

uniform sampler2D u_tex0;
uniform sampler2D u_tex1;

uniform vec3 lightColor;

in vec4 v_col;
in vec2 v_uv;
in vec3 v_normal;

in vec3 v_pos;
in vec3 v_lightPos;
in vec3 v_viewPos;

out vec4 fragColor;

void main()
{
  vec3 ambient = lightColor * 0.1; //light color * ambientStrengh
  float specularStrengh= 0.8;

  vec3 norm       = normalize(v_normal);
  vec3 lightDir   = normalize(v_lightPos - v_pos);

  float diff      = max(dot(norm, lightDir), 0.0);
  vec3 diffuse    = diff * lightColor; // lightColor = vec3(1.0)

  vec3 viewDir    = normalize(v_viewPos - v_pos);
  vec3 reflectDir = reflect(-lightDir, norm);  

  float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular   = specularStrengh * spec * lightColor;

  fragColor       =
    vec4(ambient + diffuse + specular, 1.0) * v_col * 
    mix(texture(u_tex0, v_uv), texture(u_tex1, v_uv), 0.5); 
}
