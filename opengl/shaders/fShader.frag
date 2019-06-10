#version 330 core

out vec4 frag_color;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
  vec3 position;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 u_viewPos;

uniform sampler2D u_matrix;

in vec2 var_uv;
in vec3 var_normal;
in vec3 var_position;

void main()
{  
  vec2 uv = var_uv;
  
  vec4 diffuseColor = texture(material.diffuse, uv);
  
  //ambient
  vec3 ambient = diffuseColor.rgb * light.ambient;
  
  //diffuse
  vec3 lightDir = normalize(light.position - var_position);
  float diff = max(dot(var_normal, lightDir), 0.);
  vec3 diffuse = light.diffuse * (diffuseColor.rgb * diff);
  
  
  //specular
  vec4 specularMap = texture(material.specular, uv) + texture(u_matrix, uv);
  vec3 viewDir = normalize(u_viewPos - var_position);
  vec3 reflectDir = reflect(-lightDir, var_normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shininess);
  vec3 specular = light.specular * (specularMap.rgb * spec);
  
  vec3 res = ambient + diffuse + specular;
  
  frag_color = vec4(res, 1.);
}
