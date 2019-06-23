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
#include <map>

#include "engine/Program.hpp"
#include "engine/Texture.hpp"
#include "engine/camera.hpp"
#include "engine/Scene.hpp"
#include "engine/Model.hpp"
#include "engine/VertexBufferObject.hpp"
#include "engine/constants.hpp"
#include "engine/Framebuffer.hpp"

glm::vec3 pointLightPositions[] = {
  glm::vec3( 0.7f,  0.2f,  2.0f),
  glm::vec3( 2.3f, -3.3f, -4.0f),
  glm::vec3(-4.0f,  2.0f, -12.0f),
  glm::vec3( 0.0f,  0.0f, -3.0f)
};

std::vector<glm::vec3> c_translations = {
  glm::vec3(-1.0f, 0.0f, -1.0f),
  glm::vec3(2.0f, 0.0f, 0.0f)
};

std::vector<float> planeVertices = {
   5.0f, -0.5f,  5.0f,
  -5.0f, -0.5f,  5.0f,
  -5.0f, -0.5f, -5.0f,
  
  5.0f, -0.5f,  5.0f,
  -5.0f, -0.5f, -5.0f,
  5.0f, -0.5f, -5.0f,
};

std::vector<float> planeUv = {
  2.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 2.0f,
  
  0.0f, 2.0f,
  0.0f, 2.0f,
  2.0f, 2.0f
};

std::vector<glm::vec3> vegetation = {
  glm::vec3(-1.0f,  0.0f, -0.48f),
  glm::vec3( 2.0f,  0.0f,  0.51f),
  glm::vec3( 0.5f,  0.0f,  0.7f),
  glm::vec3(0.7f,  0.0f, -2.3f),
  glm::vec3( 0.5f,  0.0f, -0.6f)
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


int main()
{
  bool b[4];
  int v = 7;  // number to dissect
  
  b [0] =  0 != (v & (1 << 0));
  b [1] =  0 != (v & (1 << 1));
  b [2] =  0 != (v & (1 << 2));
  b [3] =  0 != (v & (1 << 3));
  
  Engine::Scene scene(800, 600, "LearnOpenGL");
  scene.init();
  
  
  Engine::Program p3("./vShader.vert", "./deph_test.frag");
  p3.link();

  Engine::Model cube_model_3("./", "cube.obj", p3);
  Engine::VBO planeVBO(planeVertices, std::vector<float>(1.0), planeUv);
  
  glm::mat4 model(1.0f);
  model = glm::mat4(1.0f);
  
  Engine::Camera camera(camPos, camPos + camFront, sceneUp);
  
  glm::mat4 projection(1.0f);
  
  //-----------
  
  Engine::Texture marble_tex("./marble.jpg");
  Engine::Texture metal_tex("./metal.png", 1);
  
  
  GLfloat width = scene.getWindowWidth();
  GLfloat height = scene.getWindowHeight();
  
  projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
  
  glm::mat4 mvp = projection * camera.getView() * model;
  
  scene.setKeyCallback(keyCallback);
  scene.setCursorPosCallback(mouseCallback);
  
  Engine::Framebuffer fbo(1600, 1200);
  
  scene.setSceneLoopUpdateCallback([&](float delta) -> void {
    
    move(delta);
    camera.computeView(camPos, camPos + cameraFront, glm::vec3(0.0, 1.0, 0.0));
    
    p3.use();
    
    model = glm::mat4(1.0f);
    mvp = projection * camera.getView() * model;
    p3.setMat4("u_MVP", mvp);
    
    metal_tex.use();
    p3.setInt("tex", metal_tex.getID());
    planeVBO.draw();
    marble_tex.use();
    p3.setInt("tex", marble_tex.getID());
    
    for (glm::vec3 curr_tr : c_translations) {
      
      model = glm::translate(model, curr_tr);
      mvp = projection * camera.getView() * model;
      p3.setMat4("u_MVP", mvp);
      cube_model_3.draw();
      
      model = glm::mat4(1.0f);
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
