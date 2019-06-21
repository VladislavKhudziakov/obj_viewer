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
  Framebuffer::Framebuffer(unsigned int framebuffer, unsigned int colorbuffer, unsigned int renderbuffer)
  {
    this->framebuffer = framebuffer;
    this->colorbuffer = colorbuffer;
    this->renderbuffer = renderbuffer;
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
}

