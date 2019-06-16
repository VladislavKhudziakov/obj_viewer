

#version 330 core

out vec4 frag_color;

in vec2 var_uv;
in vec3 var_normal;
in vec3 var_position;

uniform sampler2D tex;

void main()
{
  vec4 final_color = texture(tex, var_uv);
  
  if (final_color.a < 0.001) {
    discard;
  }
  
  frag_color = final_color;
}
