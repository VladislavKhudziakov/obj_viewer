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
    
    while (!glfwWindowShouldClose(window))
    {
      glfwPollEvents();
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glEnable(GL_DEPTH_TEST);
      glClear(GL_COLOR_BUFFER_BIT);
      glClear(GL_DEPTH_BUFFER_BIT);
  
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
}

