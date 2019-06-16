//
//  Scene.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Scene.hpp"

namespace Engine {
  Scene::Scene(int w, int h, const std::string& sceneName)
  {
    windowWidth = w;
    windowHeight = h;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", nullptr, nullptr);
    
    if (window == nullptr)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  
  
  int Scene::init()
  {
    if (glewInit() != GLEW_OK)
    {
      std::cout << "Failed to initialize GLEW" << std::endl;
      return -1;
    }
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    glViewport(0, 0, width, height);
    
    return 0;
  }
  
  
  GLFWwindow* Scene::getWindow() const noexcept
  {
    return window;
  }
  
  
  int Scene::getWindowWidth() const noexcept
  {
    return windowWidth;
  }
  
  
  int Scene::getWindowHeight() const noexcept
  {
    return windowHeight;
  }
  
  
  void Scene::StartSceneLoop()
  {
    lastTime = glfwGetTime();
    
    if (keyCallback) glfwSetKeyCallback(window, keyCallback);
    if (cursorPosCallback) glfwSetCursorPosCallback(window, cursorPosCallback);
    
    while (!glfwWindowShouldClose(window))
    {
      glfwPollEvents();
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glEnable(GL_DEPTH_TEST);
      
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
      float now = glfwGetTime();
      float delta = now - lastTime;
      lastTime = now;
      
      onUpdate(delta);
      
      glfwSwapBuffers(window);
    }
  }
  
  
  void Scene::setSceneLoopUpdateCallback(std::function<void(float)> callback)
  {
    onUpdate = callback;
  }
  
  
  void Scene::setKeyCallback(void(*callback)(GLFWwindow*, int, int, int, int))
  {
    keyCallback = callback;
  }
  
  
  void Scene::setCursorPosCallback(void(*callback)(GLFWwindow*, double, double))
  {
    cursorPosCallback = callback;
  }
  
  
  void Scene::enableBlengind(unsigned long mode)
  {
    switch (mode) {
      case BLENDING_ALPHA:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
        
      case BLENDING_MULTIPLY:
        glEnable(GL_BLEND);
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        break;
        
      case BLENDING_ADD:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
        break;
        
      case BLENDING_SCREEN:
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
        break;
        
      default:
        std::cout << "BLENDING::ERROR::INVALID_MODE\n";
        break;
    }
  }
  
  
  void Scene::disableBlending()
  {
    glDisable(GL_BLEND);
  }
  
  
  void Scene::enableCullFacing(unsigned long mode)
  {
    switch (mode) {
      case CULL_FACING_FRONT:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);
        break;
        
      case CULL_FACING_BACK:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        break;
        
      default:
        std::cout << "CULL_FACING::ERROR::INVALID_MODE\n";
        break;
    }
  }
  
  
  void Scene::disableCullFacing()
  {
    glDisable(GL_CULL_FACE);
  }
}

