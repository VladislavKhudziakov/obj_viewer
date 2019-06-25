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
  Texture::Texture(const std::string& imgName, int tex_slot)
    : tex_id(tex_slot)
  {
    unsigned char* img = SOIL_load_image(
      imgName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    SOIL_free_image_data(img);
    glBindTexture(GL_TEXTURE_2D, 0);
  };
  
  void Texture::use() const noexcept
  {
    glActiveTexture(GL_TEXTURE0 + tex_id);
    glBindTexture(GL_TEXTURE_2D, texture);
  }
  
  
  unsigned int Texture::get() const noexcept
  {
    return texture;
  }
  
  unsigned int Texture::getID() const noexcept
  {
    return tex_id;
  }
}
