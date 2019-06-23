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

namespace Engine
{
  class Texture
  {
  private:
    unsigned int texture;
    unsigned int tex_id;
    int width;
    int height;
    
  public:
    Texture() { };
    Texture(const std::string&, int tex_slot = 0);
    ~Texture() { };
    void use() const noexcept;
    unsigned int get() const noexcept;
    unsigned int getID() const noexcept;
  };
}

#endif /* Texture_hpp */
