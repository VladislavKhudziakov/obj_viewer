#version 330 core

out vec4 frag_color;

uniform vec3 u_color;
uniform sampler2D u_tex;
uniform sampler2D u_tex2;


in vec2 var_uv;

void main()
{  
  vec2 uv = var_uv;
  uv.y = 1. - uv.y;
  frag_color = texture(u_tex, var_uv) * texture(u_tex2, uv);
}
