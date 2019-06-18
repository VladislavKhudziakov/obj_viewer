
#version 330 core

layout (location = 0) in vec3 position;

layout (location = 1) in vec2 attr_uv;

out vec2 var_uv;

void main()
{
  vec2 pos = position.xy;
  gl_Position = vec4(pos, 0.0, 1.0);
  var_uv = attr_uv;
}
