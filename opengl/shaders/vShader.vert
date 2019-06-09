#version 330 core

layout (location = 0) in vec3 position;

layout (location = 1) in vec2 attr_uv;

out vec2 var_uv;

uniform mat4 u_model;
uniform mat4 u_MVP;

void main()
{
  gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1.0);
  var_uv = attr_uv;
}
