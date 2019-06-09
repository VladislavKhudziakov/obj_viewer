//
//  Scene.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

//openGL libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace Engine
{
  class Scene
  {
    GLFWwindow* window;
    int windowWidth;
    int windowHeight;
    
  public:
    Scene(int, int, const std::string&);
    int init();
    
    GLFWwindow* getWindow() const noexcept;
    
    int getWindowWidth() const noexcept;
    int getWindowHeight() const noexcept;
  };
}

#endif /* Scene_hpp */
