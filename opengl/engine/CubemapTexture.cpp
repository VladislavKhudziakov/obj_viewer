//
//  CubemapTexture.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/26/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "CubemapTexture.hpp"

namespace Engine {
  CubemapTexture::CubemapTexture(const std::vector<std::string>& textures, int texSlot)
  :ITexture()
  {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    
    unsigned int i = 0;
    
    for (auto currTex : textures) {
      int width, height;
      
      unsigned char* imgData = SOIL_load_image(currTex.c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
      
      if (imgData) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
      } else {
        std::cout << "Cubemap texture failed to load at path: " << currTex << std::endl;
      }
      
      i++;
      
      SOIL_free_image_data(imgData);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  }
  
  
  void CubemapTexture::use(int textureSlot) const
  {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
  }
  
  unsigned int CubemapTexture::get() const
  {
    return texture;
  }
}
