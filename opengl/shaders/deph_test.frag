
#version 330 core

out vec4 frag_color;

in vec2 var_uv;
in vec3 var_position;

uniform sampler2D tex;

float zNear = 0.1;
float zFar  = 100.0;

float LinearizeDepth(float depth)
{
  float z = depth * 2.0 - 1.0;
  return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));
}


void main()
{
  frag_color = texture(tex, var_uv);
}
