//
//  Texture.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Texture.hpp"

namespace Engine
{  
  Texture::Texture(const std::string& imgName, unsigned int texSlot)
  {
    img = SOIL_load_image(imgName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    
    glGenTextures(1, &texture);
  
    textureSlot = texSlot >= 32 ? 0 : texSlot;
    
    glActiveTexture(GL_TEXTURE0+textureSlot);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(
     GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    
    glGenerateMipmap(GL_TEXTURE_2D);
  };
  
  
  Texture::~Texture()
  {
    SOIL_free_image_data(img);
  }
  
  
  unsigned int Texture::getSlot() const noexcept
  {
    return textureSlot;
  }
}
