#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "engine/Program.hpp"
#include "engine/VertexBufferObject.hpp"
#include "engine/Texture.hpp"
#include "engine/camera.hpp"
#include "engine/Scene.hpp"
#include <functional>

float vertices[] = {
  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  
  -0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  
  0.5f,  0.5f,  0.5f,
  0.5f,  0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f, -0.5f,  0.5f,
  0.5f,  0.5f,  0.5f,
  
  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,
  
  -0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
};


float normals[] = {
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
  
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  
  0.0f, -1.0f,  0.0f,
  0.0f, -1.0f,  0.0f,
  0.0f, -1.0f,  0.0f,
  0.0f, -1.0f,  0.0f,
  0.0f, -1.0f,  0.0f,
  0.0f, -1.0f,  0.0f,
  
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f
};


float uv[] = {
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,
  0.0f, 0.0f,
  
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,
  0.0f, 0.0f,
  
  1.0f, 0.0f,
  0.0f, 1.0f,
  0.0f, 1.0f,
  0.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 0.0f,
  
  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,
  0.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 0.0f,
  
  0.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 0.0f,
  1.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 1.0f,
  
  0.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 0.0f,
  1.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 1.0f
};


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



int main()
{
  Engine::Scene scene(800, 600, "LearnOpenGL");
  scene.init();

  Engine::Program p("./vShader.vert", "./fShader.frag");
  p.link();
  
  Engine::Program p2("./vShader.vert", "./fShaderLight.frag");
  p2.link();
  
  Engine::VBO vbo(vertices, sizeof(vertices), uv, sizeof(uv), normals, sizeof(normals));
  
  Engine::VBO vbo2(vertices, sizeof(vertices));
  
  Engine::Texture t("./container2.png");
  Engine::Texture t2("./container2_specular.png", 1);
  Engine::Texture t3("./matrix.jpg", 2);
  
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
    p.setInt("material.diffuse", t.getSlot());
    p.setInt("material.specular", t2.getSlot());
    p.setInt("u_matrix", t3.getSlot());
    
    move(delta);
    
    camera.computeView(camPos, camPos + cameraFront, glm::vec3(0.0, 1.0, 0.0));
    
    model = glm::mat4(1.0f);
//    model = glm::rotate(model, GLfloat(glfwGetTime()), glm::vec3(1.0, 0.0, 0.0));
    
    float lightPosX = sin(glm::radians(glfwGetTime() * 50.0f)) * 2.5;
    float lightPosZ = cos(glm::radians(glfwGetTime() * 50.0f)) * 2.5;
    lightPos = glm::vec3(lightPosX, lightPos.y, lightPosZ);
    mvp = projection * camera.getView() * model;
    
    p.setMat4("u_MVP", mvp);
    
    p.setVec3("material.ambient",  glm::vec3(1.0f, 0.5f, 0.31f));
    p.setVec3("material.diffuse",  glm::vec3(1.0f, 0.5f, 0.31f));
    p.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    p.setFloat("material.shininess", 16.0f);
    
    p.setVec3("light.ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
    p.setVec3("light.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
    p.setVec3("light.specular", glm::vec3(2.0f, 2.0f, 2.0f));
    p.setVec3("light.position", lightPos);
    
    p.setVec3("u_viewPos", camPos);
    p.setMat4("u_transposed_modes", glm::transpose(glm::inverse(model)));
    p.setMat4("u_model", model);
    
    vbo.draw();
    
    p2.use();
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    mvp = projection * camera.getView() * model;
    
    p2.setMat4("u_MVP", mvp);
    vbo2.draw();
  });
  
  
  scene.StartSceneLoop();
  
  vbo.del();
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
