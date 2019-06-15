#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <functional>
#include <iterator>

#include "engine/Program.hpp"
#include "engine/Texture.hpp"
#include "engine/camera.hpp"
#include "engine/Scene.hpp"
#include "engine/Model.hpp"

glm::vec3 pointLightPositions[] = {
  glm::vec3( 0.7f,  0.2f,  2.0f),
  glm::vec3( 2.3f, -3.3f, -4.0f),
  glm::vec3(-4.0f,  2.0f, -12.0f),
  glm::vec3( 0.0f,  0.0f, -3.0f)
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f, -2.0f, -5.3f),
};

std::vector<float> vertices;
std::vector<float> uv;
std::vector<float> normals;
std::vector<unsigned int> indices;

float camFront;

glm::vec3 camPos(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 sceneUp(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightColor(1.0f);

bool keys[1024];

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double x, double y);

void move(float delta);

bool isFirst = true;
float lastX;
float lastY;

float yaw = -90.0f;
float pitch = 0.0f;


void processNode(const aiScene* scene);

int main()
{
  Engine::Scene scene(800, 600, "LearnOpenGL");
  scene.init();
  
  Engine::Program p("./vShader.vert", "./fShader.frag");
  p.link();
  
  Engine::Program p2("./vShader.vert", "./fShaderLight.frag");
  p2.link();
  
  Engine::Model suit_model("./nanosuit/", "nanosuit.obj");
  Engine::Model cube_model("./", "cube.obj");
  
  glm::mat4 model(1.0f);
  model = glm::mat4(1.0f);
  
  Engine::Camera camera(camPos, camPos + camFront, sceneUp);
  
  glm::mat4 projection(1.0f);
  
  GLfloat width = scene.getWindowWidth();
  GLfloat height = scene.getWindowHeight();
  
  projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
  
  glm::mat4 mvp = projection * camera.getView() * model;
  
  scene.setKeyCallback(keyCallback);
  scene.setCursorPosCallback(mouseCallback);
  
  scene.setSceneLoopUpdateCallback([&](float delta) -> void {
    p.use();
    
    move(delta);
    
    camera.computeView(camPos, camPos + cameraFront, glm::vec3(0.0, 1.0, 0.0));
    
    p.setVec3("material.ambient",  glm::vec3(1.0f, 0.5f, 0.31f));
    p.setVec3("material.diffuse",  glm::vec3(1.0f, 0.5f, 0.31f));
    p.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    p.setFloat("material.shininess", 32.0f);
    
    p.setVec3("dirLight.direction", glm::vec3(0.2f, 1.0f, 0.3f));
    p.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    p.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    p.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    
    
    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++) {
      std::string pointLightTemplate = "pointLights[" + std::to_string(i) + "]";
      
      p.setVec3(pointLightTemplate + ".position", pointLightPositions[i]);
      p.setVec3(pointLightTemplate + ".ambient", glm::vec3(0.05f, 0.05f, 0.05f));
      p.setVec3(pointLightTemplate +".diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
      p.setVec3(pointLightTemplate + ".specular", glm::vec3(1.0f, 1.0f, 1.0f));
      p.setFloat(pointLightTemplate + ".constant", 1.0f);
      p.setFloat(pointLightTemplate + ".linear", 0.09);
      p.setFloat(pointLightTemplate + ".quadratic", 0.032);
    }

    
    p.setVec3("u_viewPos", camPos);
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[0]);
    model = glm::rotate(model, GLfloat(glfwGetTime()), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(0.2f));
    mvp = projection * camera.getView() * model;

    p.setMat4("u_MVP", mvp);
    p.setMat4("u_transposed_modes", glm::transpose(glm::inverse(model)));
    p.setMat4("u_model", model);
    
    for (auto mesh : suit_model.getMeshes()) {
      
      p.setInt("material.diffuse", mesh.getDiffTexture().getSlot());
      
      if (mesh.getSpecTexture().getSlot() < 32) {
        p.setInt("material.specular", mesh.getSpecTexture().getSlot());
      }
      
      mesh.draw();
    }
    
    p2.use();
    
    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.2f));
      mvp = projection * camera.getView() * model;
      p2.setMat4("u_MVP", mvp);
      cube_model.draw();
    }
  });
  
  
  scene.StartSceneLoop();
  
  glfwTerminate();
  return 0;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE) {
    glfwTerminate();
  } else {
    
    if (action == GLFW_PRESS) {
      keys[key] = true;
    }
    
    if (action == GLFW_RELEASE) {
      keys[key] = false;
    }
  }
}


void move(float delta)
{
  float camSpeed = 5.0f * delta;
  
  if (keys[GLFW_KEY_W]) {
    camPos += cameraFront * camSpeed;
  }
  
  if (keys[GLFW_KEY_A]) {
    camPos -= glm::normalize(glm::cross(cameraFront, sceneUp)) * camSpeed;
  }
  
  if (keys[GLFW_KEY_S]) {
    camPos -= cameraFront * camSpeed;
  }
  
  if (keys[GLFW_KEY_D]) {
    camPos += glm::normalize(glm::cross(cameraFront, sceneUp)) * camSpeed;
  }
}


void mouseCallback(GLFWwindow* window, double x, double y)
{
  if (isFirst) {
    isFirst = false;
    lastX = x;
    lastY = y;
  }
  
  float xOffset = lastX - x;
  float yOffset = lastY - y;
  
  lastX = x;
  lastY = y;
  
  float sensivity = 0.05;
  
  xOffset *= sensivity;
  yOffset *= sensivity;
  
  yaw -= xOffset;
  pitch += yOffset;
  
  if(pitch > 89.0f)
    pitch =  89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;
  
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  
  cameraFront = glm::normalize(front);
}
