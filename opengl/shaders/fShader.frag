#version 330 core

out vec4 frag_color;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform float u_ambientStr;
uniform float u_specularStr;

uniform sampler2D u_tex;
uniform sampler2D u_tex2;

in vec2 var_uv;
in vec3 var_normal;
in vec3 var_position;

void main()
{  
  vec2 uv = var_uv;
  uv.y = 1. - uv.y;
  
  vec3 lightDir = normalize(u_lightPos - var_position);
  vec3 viewDir = normalize(u_viewPos - var_position);
  
  vec3 reflectDir = reflect(-lightDir, var_normal);
  
  float nDotL = max(dot(var_normal, lightDir), 0.);
  
  float spec = pow(max(dot(viewDir, reflectDir), 0.), 64.0);
  
  vec3 specular = u_lightColor * spec * u_specularStr;
  
  vec3 objColor = (texture(u_tex, var_uv) * texture(u_tex2, uv)).rgb;
  vec3 ambient = u_lightColor * u_ambientStr;
  
  frag_color = vec4(objColor * (nDotL + ambient + specular), 1.);
}
