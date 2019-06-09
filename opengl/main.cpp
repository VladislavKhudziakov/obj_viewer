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


int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  
  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  
  glewExperimental = GL_TRUE;
  
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  
  glViewport(0, 0, width, height);
  
  Engine::Program p("./vShader.vert", "./fShader.frag");
  p.link();
  
  Engine::VBO vbo(vertices, sizeof(vertices), uv, sizeof(uv));
  
  Engine::Texture t("./container.jpg");
  Engine::Texture t2("./awesomeface.png", 1);
  
  
  glm::vec3 camPos(0.0f, 0.0f, 3.0f);
  glm::vec3 camTarget(0.0f, 0.0f, 0.0f);
  glm::vec3 sceneUp(0.0f, 1.0f, 0.0f);
  
  glm::mat4 model(1.0f);
  model = glm::mat4(1.0f);
  model = glm::rotate(model, 20.0f, glm::vec3(1.0, 0.0, 0.0));
  
  Engine::Camera c(camPos, camTarget, sceneUp);
  
  glm::mat4 projection(1.0f);
  projection = glm::perspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
  
  glm::mat4 mvp = projection * c.getView() * model;
  
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    p.use();
    glUniform1i(glGetUniformLocation(p.get(), "u_tex"), t.getSlot());
    glUniform1i(glGetUniformLocation(p.get(), "u_tex2"), t2.getSlot());
    
    unsigned int u_mvp = glGetUniformLocation(p.get(), "u_MVP");
    
    GLfloat radius = 10.0f;
    GLfloat camX = sin(glfwGetTime()) * radius;
    GLfloat camZ = cos(glfwGetTime()) * radius;
    
    c.computeView(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    int size = sizeof(cubePositions) / sizeof(glm::vec3);
    for (int i = 0; i < size; i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      GLfloat angle = 20.0f * i;
      model = glm::rotate(model, GLfloat(angle + glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));
      mvp = projection * c.getView() * model;
      glUniformMatrix4fv(u_mvp , 1, GL_FALSE, glm::value_ptr(mvp));
      
      vbo.draw();
    }
    
    glfwSwapBuffers(window);
  }
  
  vbo.del();
  glfwTerminate();
  return 0;
}
