#version 330 core

out vec4 frag_color;

in vec3 var_skybox_uv;
uniform samplerCube skybox;

void main()
{
  frag_color = texture(skybox, var_skybox_uv);
//  frag_color = vec4(1.);
}
