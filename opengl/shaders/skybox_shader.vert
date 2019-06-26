#version 330 core

layout (location = 0) in vec3 position;

out vec3 var_skybox_uv;

uniform mat4 u_MVP;

void main()
{
  var_skybox_uv = position;
  vec4 pos = u_MVP * vec4(position, 1.0);
  gl_Position = pos.xyww;
}
