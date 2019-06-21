//
//  Scene.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "Framebuffer.hpp"
#include "constants.hpp"
#include "VertexBufferObject.hpp"

namespace Engine
{
  class Scene
  {
  private:
    GLFWwindow* window;
    int windowWidth;
    int windowHeight;
    
    float lastTime;
    
    std::function<void(float)> onUpdate;
    
    std::map<std::string, Framebuffer> activeFramebuffers;
    
    void(*keyCallback)(GLFWwindow*, int, int, int, int);
    void(*cursorPosCallback)(GLFWwindow*, double, double);
    
  public:
    Scene(int, int, const std::string&);
    int init();
    
    GLFWwindow* getWindow() const noexcept;
    
    int getWindowWidth() const noexcept;
    int getWindowHeight() const noexcept;
    
    void StartSceneLoop();
    void setSceneLoopUpdateCallback(std::function<void(float)>);
    void setKeyCallback(void(*callback)(GLFWwindow*, int, int, int, int));
    void setCursorPosCallback(void(*callback)(GLFWwindow*, double, double));
    
    void enableBlengind(unsigned long);
    void disableBlending();
    
    void enableCullFacing(unsigned long);
    void disableCullFacing();
    
    void initFramebuffer(const std::string&);
    void renderInFramebuffer(const std::string&,
     unsigned long bit_mask = 0,
     float r = 0, float g = 0, float b = 0, float a = 1.);
    void stopRenderInFrameBuffer(const std::string&);
    const Framebuffer& getFramebuffer(const std::string&);
    
    VBO generate2DRect();
  };
}

#endif /* Scene_hpp */
