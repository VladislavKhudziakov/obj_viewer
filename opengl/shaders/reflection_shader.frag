
#version 330 core

out vec4 frag_color;

in vec2 var_uv;
in vec3 var_normal;
in vec3 var_position;

uniform samplerCube skybox_tex;
uniform vec3 u_viewPos;

void main()
{
  float ratio = 1. / 1.52;
  vec3 I = normalize(var_position - u_viewPos);
//  vec3 R = refract(I, var_normal, ratio);
  vec3 R = reflect(I, var_normal);
  frag_color = texture(skybox_tex, R);
}
