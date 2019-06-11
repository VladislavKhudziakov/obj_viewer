#version 330 core

out vec4 frag_color;

#define NR_POINT_LIGHTS 4

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


struct DirLight {
  vec3 direction;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


struct PointLight {
  vec3 position;
  
  float constant;
  float linear;
  float quadratic;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


uniform Material material;

uniform DirLight dirLight;

#ifdef NR_POINT_LIGHTS
uniform PointLight pointLights[NR_POINT_LIGHTS];
#endif

uniform vec3 u_viewPos;

uniform sampler2D u_matrix;

in vec2 var_uv;
in vec3 var_normal;
in vec3 var_position;


vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 vertPos, vec3 viewDir);

void main()
{  
  
  vec3 res = vec3(0.0);
  
  vec3 normal = normalize(var_normal);
  vec3 viewDirection = normalize(u_viewPos - var_position);
  
  res += calculateDirLight(dirLight, normal, viewDirection);
  
  for (int i = 0; i < NR_POINT_LIGHTS; i++) {
    res += calculatePointLight(pointLights[i], normal, var_position, viewDirection);
  }
  
  frag_color = vec4(res, 1.);
}


vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
  vec3 lightDirection = normalize(-light.direction);
  
  vec3 diffuseColor = texture(material.diffuse, var_uv).rgb;
  
  //ambient
  vec3 ambient = light.ambient * diffuseColor;
  
  //diffuse
  float diff = max(dot(lightDirection, normal), 0.0);
  vec3 diffuse = light.diffuse * diffuseColor * diff;
  
  //specular
  vec3 specularMap = texture(material.specular, var_uv).rgb;
  vec3 reflectDir = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * specularMap * spec;
  
  return ambient + diffuse + specular;
}


vec3 calculatePointLight(PointLight light, vec3 normal, vec3 vertPos, vec3 viewDir)
{
  vec3 lightDirection = normalize(light.position - vertPos);
  
  vec3 diffuseColor = texture(material.diffuse, var_uv).rgb;
  
  //ambient
  vec3 ambient = light.ambient * diffuseColor;
  
  //diffuse
  float diff = max(dot(lightDirection, normal), 0.0);
  vec3 diffuse = light.diffuse * diffuseColor * diff;
  
  //specular
  vec3 specularMap = texture(material.specular, var_uv).rgb;
  vec3 reflectDir = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * specularMap * spec;
  
  float dist = length(light.position - vertPos);
  float attenuation = 1.0 / (light.constant + light.linear * dist +
                             light.quadratic * (dist * dist));
  
  return ambient * attenuation + diffuse * attenuation + specular * attenuation;
}
