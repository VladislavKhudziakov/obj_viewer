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
  Framebuffer::Framebuffer(const std::string& name, int width, int height)
  {
    this->name = name;
    this->width = width;
    this->height = height;
  }
  
  
  void Framebuffer::init(unsigned int framebuffer, unsigned int colorbuffer, unsigned int renderbuffer)
  {
    if (framebuffer) {
      this->framebuffer = framebuffer;
    } else {
      glGenFramebuffers(1, &this->framebuffer);
      glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
    }
    
    if (colorbuffer) {
      this->colorbuffer = colorbuffer;
    } else {
      glGenTextures(1, &this->colorbuffer);
      
      glActiveTexture(GL_TEXTURE0 + this->colorbuffer);
      glBindTexture(GL_TEXTURE_2D, this->colorbuffer);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    if (renderbuffer) {
      this->renderbuffer = renderbuffer;
    } else {
      glGenRenderbuffers(1, &this->renderbuffer);
      glBindRenderbuffer(GL_RENDERBUFFER, this->renderbuffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderbuffer);
    }
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
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
  
  
  const std::string& Framebuffer::getName() const
  {
    return name;
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

