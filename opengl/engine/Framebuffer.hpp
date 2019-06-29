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

#include "EmptyTexture.hpp"
#include "RenderbufferObject.hpp"
#include "FramebufferObject.hpp"

namespace Engine
{
  class Framebuffer
  {
  private:
    int width, height;
    unsigned long render_bit_mask;
    bool isRenderIn;
    
    EmptyTexture textureColorBuffer;
    RBO renderbuffer;
    FBO framebuffer;
    
    struct ClearColor {
      float r, g, b, a;
    };
    
    ClearColor clearColor;
    
  public:
    Framebuffer() : textureColorBuffer() { };
    Framebuffer(int widht, int height);
    const EmptyTexture& getColorbuffer() const;
    void renderIn(unsigned long bit_mask, float r = 0, float g = 0, float b = 0, float a = 0);
    void stopRenderIn();
    bool IsRenderIn() const;
  };
}
#endif /* Framebuffer_hpp */
