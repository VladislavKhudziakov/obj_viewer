//
//  Framebuffer.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/21/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Framebuffer.hpp"

namespace Engine
{
  Framebuffer::Framebuffer(int width, int height)
  : framebuffer(), width(width), height(height)
  {
    textureColorBuffer = EmptyTexture(width, height);
    
    framebuffer.attachColorbuffer(textureColorBuffer);
    renderbuffer = RBO(width, height);
    
    framebuffer.attachRenderbuffer(renderbuffer);
    framebuffer.checkStatus();
  }
  
  
  const EmptyTexture& Framebuffer::getColorbuffer() const
  {
    return textureColorBuffer;
  }
  
  
  void Framebuffer::renderIn(unsigned long bit_mask, float r, float g, float b, float a)
  {
    isRenderIn = true;
    render_bit_mask = bit_mask;
    framebuffer.use();
    
    if (bit_mask & (1 << 0)) {
      glEnable(GL_DEPTH_TEST);
      glClear(GL_DEPTH_BUFFER_BIT);
    }
    
    clearColor.r = r;
    clearColor.g = g;
    clearColor.b = b;
    clearColor.a = a;
    
    if (bit_mask & (2 << 0)) {
      glClearColor(r, g, b, a);
      glClear(GL_COLOR_BUFFER_BIT);
    }
  }
  
  
  void Framebuffer::stopRenderIn()
  {
    isRenderIn = false;
    framebuffer.unuse();
    
    if (render_bit_mask & (1 << 0)) {
      glDisable(GL_DEPTH_TEST);
      glClear(GL_DEPTH_BUFFER_BIT);
    }
    
    if (render_bit_mask & (2 << 0)) {
      glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
      glClear(GL_COLOR_BUFFER_BIT);
    }
  }
  
  
  bool Framebuffer::IsRenderIn() const
  {
    return isRenderIn;
  }

}

