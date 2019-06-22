//
//  Framebuffer.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/21/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace Engine
{
  class Framebuffer
  {
  private:
    int width, height;
    unsigned int colorbuffer, renderbuffer, framebuffer;
    unsigned long render_bit_mask;
    bool isRenderIn;
    
    struct ClearColor {
      float r, g, b, a;
    };
    
    ClearColor clearColor;
    
  public:
    Framebuffer() { };
    Framebuffer(int widht, int height);
    unsigned int getColorbuffer() const;
    unsigned int getRenderbuffer() const;
    unsigned int get() const;
    void renderIn(unsigned long bit_mask, float r = 0, float g = 0, float b = 0, float a = 0);
    void stopRenderIn();
    bool IsRenderIn() const;
  };
}
#endif /* Framebuffer_hpp */
