#version 330 core

layout (location = 0) in vec3 position;

layout (location = 1) in vec2 attr_uv;

layout (location = 2) in vec3 attr_normals;

out vec2 var_uv;
out vec3 var_normal;
out vec3 var_position;

uniform mat4 u_transposed_modes;
uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
  gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1.0);
  var_uv = attr_uv;
  var_normal = normalize(vec3(u_transposed_modes * vec4(attr_normals, 1.)));
  var_position = vec3(u_model * vec4(position, 1.));
}
