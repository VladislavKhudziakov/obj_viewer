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
  Texture2D::Texture2D(const std::string& imgName)
  {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    unsigned char* img = SOIL_load_image(
      imgName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    SOIL_free_image_data(img);
    glBindTexture(GL_TEXTURE_2D, 0);
  };
  
  void Texture2D::use(int textureSlot) const
  {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texture);
  }
  
  unsigned int Texture2D::get() const
  {
    return texture;
  }
}
