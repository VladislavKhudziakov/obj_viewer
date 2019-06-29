//
//  RenderbufferObject.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef RenderbufferObject_hpp
#define RenderbufferObject_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
  class RBO
  {
    unsigned int rbo;
    int width, height;
  public:
    RBO() : rbo(), width(), height() { };
    RBO(int, int);
    unsigned int get() const;
  };
}
#endif /* RenderbufferObject_hpp */
