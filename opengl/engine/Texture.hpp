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

namespace Engine
{
  class Texture
  {
  private:
    unsigned int texture;
    unsigned int textureSlot;
    unsigned char* img;
    int width;
    int height;
    
  public:
    Texture(const std::string&, unsigned int texSlot = 0);
    ~Texture();
    unsigned int getSlot() const noexcept;
  };
}

#endif /* Texture_hpp */
