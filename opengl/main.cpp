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
  "right.jpg",
  "left.jpg",
  "top.jpg",
  "bottom.jpg",
  "front.jpg",
  "back.jpg"
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
  
  Engine::Program p("./vShader.vert", "./fShader.frag");
  p.link();
  
  Engine::Program p2("./vShader.vert", "./fShaderLight.frag");
  p2.link();
  
  Engine::Program p3("./vShader.vert", "./deph_test.frag");
  p3.link();
  
  Engine::Program p4("./vShader.vert", "./shader_blending.frag");
  p4.link();
  
  Engine::Program postprocessing_shaders("./postprocessing_vShader.vert", "./postprocessing_fShader.frag");
  postprocessing_shaders.link();
  
  Engine::Model suit_model("./nanosuit/", "nanosuit.obj", p);
  Engine::Model cube_model("./", "cube.obj", p2);
  Engine::Model cube_model_3("./", "cube.obj", p3);
  
  Engine::VBO planeVBO = scene.generate2DRect();
  Engine::VBO transparentVBO = scene.generate2DRect();
  
  Engine::VBO postprocessing_plane = scene.generate2DRect();
  
  glm::mat4 model(1.0f);
  model = glm::mat4(1.0f);
  
  Engine::Camera camera(camPos, camPos + camFront, sceneUp);
  
  glm::mat4 projection(1.0f);
  
  Engine::Texture marble("./marble.jpg");
  cube_model_3.getMeshes().at("cube").setTexture("diffuse", marble);
  Engine::Texture metal("./metal.png");
  Engine::Texture window("./blending_transparent_window.png");
  
  GLfloat width = scene.getWindowWidth();
  GLfloat height = scene.getWindowHeight();
  
  projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
  
  glm::mat4 mvp = projection * camera.getView() * model;
  
  scene.setKeyCallback(keyCallback);
  scene.setCursorPosCallback(mouseCallback);
  
  Engine::Framebuffer fbo(1600, 1200);
  
  
  Engine::Program skyboxShader("./skybox_shader.vert", "./skybox_shader.frag");
//  skyboxShader.link();
  
//  unsigned int skybox_tex;
//  glGenTextures(1, &skybox_tex);
//  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_tex);
//  unsigned int i = 0;
//
//  for (auto currTex : skyboxTextures) {
//    int width, height;
//
//    unsigned char* imgData = SOIL_load_image(("./skybox/" + currTex).c_str(),
//                                             &width, &height, 0, SOIL_LOAD_RGB);
//
//    if (imgData) {
//      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//                   0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
//    } else {
//       std::cout << "Cubemap texture failed to load at path: " << "./skybox" + currTex << std::endl;
//    }
//
//    i++;
//
//    SOIL_free_image_data(imgData);
//  }
//
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  
//  Engine::VBO skybox(skyboxVertices, std::vector<float>(1.), std::vector<float>(1.));
  
  Engine::Skybox skybox("./skybox/", skyboxTextures, skyboxShader);
  
  scene.setSceneLoopUpdateCallback([&](float delta) -> void {
    
    fbo.renderIn(Engine::FRAMEBUFFER_DEPTH_TEST_ACTIVATE | Engine::FRAMEBUFFER_CLEAR_COLOR);
    
    move(delta);
    
    camera.computeView(camPos, camPos + cameraFront, glm::vec3(0.0, 1.0, 0.0));
    
    skyboxShader.use();
    glm::mat4 skyboxView = glm::mat4(glm::mat3(camera.getView()));
    model = glm::mat4(1.0f);
    mvp = projection * skyboxView * model;
    skyboxShader.setMat4("u_MVP", mvp);
    
    skybox.render();
    
//    glDepthMask(GL_FALSE);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_tex);
//    skyboxShader.setInt("skybox", 0);
//    skybox.draw();
//    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//    glDepthMask(GL_TRUE);
    
    p.use();
    
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
    
    suit_model.draw();
    
    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.2f));
      mvp = projection * camera.getView() * model;
      p2.setMat4("u_MVP", mvp);
      cube_model.draw();
    }
    
    p3.use();
    metal.use();
    p3.setInt("tex", metal.getID());
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mvp = projection * camera.getView() * model;
    p3.setMat4("u_MVP", mvp);
    
    planeVBO.draw();
    
    scene.enableCullFacing(Engine::CULL_FACING_BACK);
    
    p3.use();
    
    for (glm::vec3 curr_tr : c_translations) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, curr_tr);
      mvp = projection * camera.getView() * model;
      p3.setMat4("u_MVP", mvp);
      cube_model_3.draw();
    }
    
    scene.disableCullFacing();
    
    scene.enableBlengind(Engine::BLENDING_ALPHA);

    p4.use();
    window.use();
    p4.setInt("tex", window.getID());

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
      p4.setMat4("u_MVP", mvp);
      transparentVBO.draw();
    }

    scene.disableBlending();
    
    fbo.stopRenderIn();
    
    postprocessing_shaders.use();
    fbo.useAsTexture();
    postprocessing_shaders.setInt("posprocessing_texture", fbo.getTextureID());
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
