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

#include "BaseTexture.hpp"

namespace Engine
{
  class Texture2D : public BaseTexture
  {
  private:
    int width;
    int height;
    
  public:
    Texture2D() : BaseTexture() { };
    Texture2D(const std::string&, int tex_slot = 0);
    void use() const override;
    void use(int) const override;
  };
}

#endif /* Texture_hpp */
