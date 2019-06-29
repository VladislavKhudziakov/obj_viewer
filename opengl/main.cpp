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
#include "engine/Skybox.hpp"

std::vector<float> skyboxVertices = {
  // positions
  -1.0f,  1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  
  -1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,
  
  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  
  -1.0f, -1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,
  
  -1.0f,  1.0f, -1.0f,
  1.0f,  1.0f, -1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f, -1.0f,
  
  -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
  1.0f, -1.0f,  1.0f
};

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

std::vector<std::string> skyboxTextures = {
  "./skybox/right.jpg",
  "./skybox/left.jpg",
  "./skybox/top.jpg",
  "./skybox/bottom.jpg",
  "./skybox/front.jpg",
  "./skybox/back.jpg"
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
  Engine::Scene scene(800, 600, "LearnOpenGL");
  scene.init();
  
  Engine::Program defaultShaders("./vShader.vert", "./fShader.frag");
  defaultShaders.link();
  Engine::Program lightSourcesShader("./vShader.vert", "./fShaderLight.frag");
  lightSourcesShader.link();
  Engine::Program depthTestShader("./vShader.vert", "./deph_test.frag");
  depthTestShader.link();
  Engine::Program blendingShader("./vShader.vert", "./shader_blending.frag");
  blendingShader.link();
  Engine::Program postprocessing_shaders("./postprocessing_vShader.vert", "./postprocessing_fShader.frag");
  postprocessing_shaders.link();
  Engine::Program reflectionShader("./vShader.vert", "./reflection_shader.frag");
  reflectionShader.link();
  
  Engine::Model suit_model("./nanosuit/", "nanosuit.obj", defaultShaders);
  Engine::Model cube_model("./", "cube.obj", lightSourcesShader);
  Engine::Model cube_model_3("./", "cube.obj", reflectionShader);
  
  Engine::VBO planeVBO = scene.generate2DRect();
  Engine::VBO transparentVBO = scene.generate2DRect();
  
  Engine::VBO postprocessing_plane = scene.generate2DRect();
  
  glm::mat4 model(1.0f);
  model = glm::mat4(1.0f);
  
  Engine::Camera camera(camPos, camPos + camFront, sceneUp);
  
  glm::mat4 projection(1.0f);
  
  Engine::Texture2D marble("./marble.jpg");
  cube_model_3.getMeshes().at("cube").setTexture("diffuse", marble);
  Engine::Texture2D metal("./metal.png");
  Engine::Texture2D window("./blending_transparent_window.png");
  
  GLfloat width = scene.getWindowWidth();
  GLfloat height = scene.getWindowHeight();
  
  projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
  
  glm::mat4 mvp = projection * camera.getView() * model;
  
  scene.setKeyCallback(keyCallback);
  scene.setCursorPosCallback(mouseCallback);
  
  Engine::Framebuffer fbo(1600, 1200);
  
  
  Engine::Program skyboxShader("./skybox_shader.vert", "./skybox_shader.frag");
  skyboxShader.link();
  Engine::Skybox skybox_(skyboxTextures, skyboxShader);
  
  suit_model.setEnvTex(skybox_.getTexture());
  
  scene.setSceneLoopUpdateCallback([&](float delta) -> void {
    
    fbo.renderIn(Engine::FRAMEBUFFER_DEPTH_TEST_ACTIVATE | Engine::FRAMEBUFFER_CLEAR_COLOR);
    
    move(delta);
    
    camera.computeView(camPos, camPos + cameraFront, glm::vec3(0.0, 1.0, 0.0));
    
    skyboxShader.use();
    glm::mat4 skyboxView = glm::mat4(glm::mat3(camera.getView()));
    model = glm::mat4(1.0f);
    mvp = projection * skyboxView * model;
    skyboxShader.setMat4("u_MVP", mvp);
    
    skybox_.draw();
    
    defaultShaders.use();
    
    defaultShaders.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    defaultShaders.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    defaultShaders.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    defaultShaders.setFloat("material.shininess", 32.0f);
    
    defaultShaders.setVec3("dirLight.direction", glm::vec3(0.2f, 1.0f, 0.3f));
    defaultShaders.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    defaultShaders.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    defaultShaders.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    
    
    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++) {
      std::string pointLightTemplate = "pointLights[" + std::to_string(i) + "]";
      
      defaultShaders.setVec3(pointLightTemplate + ".position", pointLightPositions[i]);
      defaultShaders.setVec3(pointLightTemplate + ".ambient", glm::vec3(0.05f, 0.05f, 0.05f));
      defaultShaders.setVec3(pointLightTemplate +".diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
      defaultShaders.setVec3(pointLightTemplate + ".specular", glm::vec3(1.0f, 1.0f, 1.0f));
      defaultShaders.setFloat(pointLightTemplate + ".constant", 1.0f);
      defaultShaders.setFloat(pointLightTemplate + ".linear", 0.09);
      defaultShaders.setFloat(pointLightTemplate + ".quadratic", 0.032);
    }
    
    defaultShaders.setVec3("u_viewPos", camPos);
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[0]);
    model = glm::rotate(model, GLfloat(glfwGetTime()), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(0.2f));
    mvp = projection * camera.getView() * model;
    
    defaultShaders.setMat4("u_MVP", mvp);
    defaultShaders.setMat4("u_transposed_modes", glm::transpose(glm::inverse(model)));
    defaultShaders.setMat4("u_model", model);
    
    suit_model.draw();
    
    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.2f));
      mvp = projection * camera.getView() * model;
      lightSourcesShader.setMat4("u_MVP", mvp);
      cube_model.draw();
    }
    
    depthTestShader.use();
    metal.use();
    depthTestShader.setInt("tex", 0);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mvp = projection * camera.getView() * model;
    depthTestShader.setMat4("u_MVP", mvp);
    
    planeVBO.draw();
    
    scene.enableCullFacing(Engine::CULL_FACING_BACK);
    reflectionShader.use();
    
    for (glm::vec3 curr_tr : c_translations) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, curr_tr);
      mvp = projection * camera.getView() * model;
      
      reflectionShader.setMat4("u_MVP", mvp);
      reflectionShader.setMat4("u_transposed_modes", glm::transpose(glm::inverse(model)));
      reflectionShader.setMat4("u_model", model);
      reflectionShader.setVec3("u_viewPos", camPos);
      skybox_.getTexture().use();
      cube_model_3.draw();
    }
    
    scene.disableCullFacing();
    
    scene.enableBlengind(Engine::BLENDING_ALPHA);

    blendingShader.use();
    window.use();
    blendingShader.setInt("tex", 0);

    std::map<float, glm::vec3> sorted;
    for (glm::vec3 curr_grass_pos : vegetation) {
      float distance = glm::distance(camera.getPosition(), curr_grass_pos);
      sorted[distance] = curr_grass_pos;
    }

    for (auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, it->second);
      model = glm::scale(model, glm::vec3(0.5, 0.5, 1.0));
      mvp = projection * camera.getView() * model;
      blendingShader.setMat4("u_MVP", mvp);
      transparentVBO.draw();
    }

    scene.disableBlending();
    
    fbo.stopRenderIn();
    
    postprocessing_shaders.use();
    fbo.getColorbuffer().use();
    postprocessing_shaders.setInt("posprocessing_texture", 0);
    postprocessing_plane.draw();
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
