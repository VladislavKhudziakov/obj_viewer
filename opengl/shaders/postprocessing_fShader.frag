

#version 330 core

out vec4 frag_color;

in vec2 var_uv;

uniform sampler2D posprocessing_texture;

void main()
{
  vec2 uv = var_uv;
  vec3 color = texture(posprocessing_texture, uv).rgb;
//  float grey = (color.x + color.y + color.z) / 3.;
  frag_color = vec4(1. - color, var_uv);
}
