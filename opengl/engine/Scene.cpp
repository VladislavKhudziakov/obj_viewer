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
    windowWidth = width;
    windowHeight = height;
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
  
  
  VBO Scene::generate2DRect()
  {
    std::vector<float> rectVertices = {
      -1.0f,  1.0f,  0.0f,
      -1.0f, -1.0f,  0.0f,
      1.0f, -1.0f,   0.0f,
      
      -1.0f,  1.0f,  0.0f,
      1.0f, -1.0f,   0.0f,
      1.0f,  1.0f,   0.0f,
    };
    
    std::vector<float> rectUV = {
      0.0f,  1.0f,
      0.0f,  0.0f,
      1.0f,  0.0f,
      
      0.0f,  1.0f,
      1.0f,  0.0f,
      1.0f,  1.0f
    };
    
    return VBO(rectVertices, std::vector<float>(1.0), rectUV);
  }
  
  
//  void initFramebuffer(std::string);
//  void renderInFramebuffer(std::string);
//  const Framebuffer& getFramebuffer();
  
  void Scene::initFramebuffer(const std::string& name)
  {
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    unsigned int texColorBuffer;
    glGenTextures(1, &texColorBuffer);

    glActiveTexture(GL_TEXTURE0 + texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

//    std::cout << texCsolorBuffer << "\n";

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
      return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    Framebuffer newFramebuffer = Framebuffer(name, windowWidth, windowHeight);
    newFramebuffer.init(framebuffer, texColorBuffer, rbo);
//    newFramebuffer.init();
    activeFramebuffers[name] = newFramebuffer;
  }
  
  
  void Scene::renderInFramebuffer(const std::string& name,
    unsigned long bit_mask, float r, float g, float b, float a)
  {
    try {
      Framebuffer currBuffer = activeFramebuffers.at(name);
      currBuffer.renderIn(bit_mask, r, g, b, a);
//      glBindFramebuffer(GL_FRAMEBUFFER, currBuffer.get());
//
//      if (bit_mask & (1 << 0)) {
//        glEnable(GL_DEPTH_TEST);
//        glClear(GL_DEPTH_BUFFER_BIT);
//      }
//
//      if (bit_mask & (2 << 0)) {
//        glClearColor(r, g, b, a);
//        glClear(GL_COLOR_BUFFER_BIT);
//      }
      
    } catch (std::out_of_range err) {
      std::cout << err.what() << std::endl;
    }
  }
  
  
  void Scene::stopRenderInFrameBuffer(const std::string& name)
  {
    try {
      Framebuffer currBuffer = activeFramebuffers.at(name);
      currBuffer.stopRenderIn();
      //      glBindFramebuffer(GL_FRAMEBUFFER, currBuffer.get());
      //
      //      if (bit_mask & (1 << 0)) {
      //        glEnable(GL_DEPTH_TEST);
      //        glClear(GL_DEPTH_BUFFER_BIT);
      //      }
      //
      //      if (bit_mask & (2 << 0)) {
      //        glClearColor(r, g, b, a);
      //        glClear(GL_COLOR_BUFFER_BIT);
      //      }
      
    } catch (std::out_of_range err) {
      std::cout << err.what() << std::endl;
    }
  }
  
  
  const Framebuffer& Scene::getFramebuffer(const std::string& name)
  {
    return activeFramebuffers.at(name);
  }
}

