//
//  Texture.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <string>
#include <iostream>

#include "ITexture.hpp"

namespace Engine
{
  class Texture2D : public ITexture
  {
  private:
    unsigned int texture;
    int width, height;
    
  public:
    Texture2D() : ITexture(), texture(), width(), height() { };
    Texture2D(const std::string&);
    void use(int textureSlot = 0) const override;
    unsigned int get() const override;
  };
}

#endif /* Texture_hpp */
