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
  Framebuffer::Framebuffer(int width, int height, int tex_id)
  : width(width), height(height), tex_id(tex_id)
  {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    glGenTextures(1, &colorbuffer);
    glBindTexture(GL_TEXTURE_2D, colorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuffer, 0);
    
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
      return;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  
  
  unsigned int Framebuffer::getColorbuffer() const
  {
    return colorbuffer;
  }
  
  
  unsigned int Framebuffer::getRenderbuffer() const
  {
    return renderbuffer;
  }
  
  
  unsigned int Framebuffer::get() const
  {
    return framebuffer;
  }
  
  
  int Framebuffer::getTextureID() const
  {
    return tex_id;
  }
  
  
  void Framebuffer::useAsTexture() const
  {
    glActiveTexture(GL_TEXTURE0 + tex_id);
    glBindTexture(GL_TEXTURE_2D, colorbuffer);
  }
  
  
  void Framebuffer::renderIn(unsigned long bit_mask, float r, float g, float b, float a)
  {
    isRenderIn = true;
    render_bit_mask = bit_mask;
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
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
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
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

