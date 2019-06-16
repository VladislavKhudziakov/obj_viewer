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
  Texture::Texture(const std::string& imgName)
  {
    unsigned char* img = SOIL_load_image(
      imgName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    
    glGenTextures(1, &texture);
    
    if (texture < 32) {
      textureSlot = texture;
    } else {
      int mulCoeff = 2;
      
      while (mulCoeff * 32 - texture < 0) {
        mulCoeff++;
      }
      
      textureSlot = 32 - (32 * mulCoeff - texture) + 1;
    }
    
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(
     GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    SOIL_free_image_data(img);
  };
  
  
  unsigned int Texture::getSlot() const noexcept
  {
    return textureSlot;
  }
}
