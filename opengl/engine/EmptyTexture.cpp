//
//  EmptyTexture.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "EmptyTexture.hpp"

namespace Engine
{
  EmptyTexture::EmptyTexture(int width, int height)
  {
    this->width = width;
    this->height = height;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  
  
  void EmptyTexture::use(int textureSlot) const
  {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texture);
  }
  
  
  unsigned int EmptyTexture::EmptyTexture::get() const
  {
    return texture;
  }
}
