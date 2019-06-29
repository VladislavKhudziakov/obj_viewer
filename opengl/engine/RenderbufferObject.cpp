//
//  RenderbufferObject.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "RenderbufferObject.hpp"

namespace Engine
{
  
  RBO::RBO(int width, int height)
  {
    this->width = width;
    this->height = height;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
  }
  
  unsigned int RBO::get() const
  {
    return rbo;
  }
}
