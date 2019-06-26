//
//  BaseTexture.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/26/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "BaseTexture.hpp"

namespace Engine {
  
  BaseTexture::BaseTexture(int textureSlot) : texID(textureSlot)
  {
    glGenTextures(1, &texture);
  }
  
  unsigned int BaseTexture::get()
  {
    return texture;
  }
  
  
  int BaseTexture::getID()
  {
    return texID;
  }
}
