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

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float camFront;

glm::vec3 camPos(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 sceneUp(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightColor(1.0f);
float ambientStr = 0.1f;
float specularStr = 0.5f;

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
  
  Engine::Texture t("./container.jpg");
  Engine::Texture t2("./awesomeface.png", 1);
  
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
  
  
//  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
//  glm::vec3 cubeColor(1.0f, 0.5f, 0.31f);
  
  scene.setSceneLoopUpdateCallback([&](float delta) -> void {
    p.use();
    glUniform1i(glGetUniformLocation(p.get(), "u_tex"), t.getSlot());
    glUniform1i(glGetUniformLocation(p.get(), "u_tex2"), t2.getSlot());
    
    unsigned int u_mvp = glGetUniformLocation(p.get(), "u_MVP");
    unsigned int u_ambientStr = glGetUniformLocation(p.get(), "u_ambientStr");
    unsigned int u_lightColor = glGetUniformLocation(p.get(), "u_lightColor");
    unsigned int u_lightPos = glGetUniformLocation(p.get(), "u_lightPos");
    unsigned int u_transposed_modes = glGetUniformLocation(p.get(), "u_transposed_modes");
    unsigned int u_specularStr = glGetUniformLocation(p.get(), "u_specularStr");
    unsigned int u_viewPos = glGetUniformLocation(p.get(), "u_viewPos");
    unsigned int u_model = glGetUniformLocation(p.get(), "u_model");
    move(delta);
    
    camera.computeView(camPos, camPos + cameraFront, glm::vec3(0.0, 1.0, 0.0));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, GLfloat(glfwGetTime()), glm::vec3(1.0, 0.0, 0.0));
    float lightPosX = sin(glm::radians(glfwGetTime() * 50.0f)) * 2.5;
    float lightPosZ = cos(glm::radians(glfwGetTime() * 50.0f)) * 2.5;
    lightPos = glm::vec3(lightPosX, lightPos.y, lightPosZ);
    mvp = projection * camera.getView() * model;
    glUniformMatrix4fv(u_mvp , 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform1f(u_ambientStr, ambientStr);
    glUniform1f(u_specularStr, specularStr);
    glUniform3fv(u_lightColor, 1, glm::value_ptr(lightColor));
    glUniform3fv(u_lightPos, 1, glm::value_ptr(lightPos));
    glUniform3fv(u_viewPos, 1, glm::value_ptr(camPos));
    glUniformMatrix4fv(u_transposed_modes , 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(model))));
    glUniformMatrix4fv(u_model , 1, GL_FALSE, glm::value_ptr(model));
    vbo.draw();
    
    p2.use();
    u_mvp = glGetUniformLocation(p2.get(), "u_MVP");
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    mvp = projection * camera.getView() * model;
    
    glUniformMatrix4fv(u_mvp , 1, GL_FALSE, glm::value_ptr(mvp));
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
