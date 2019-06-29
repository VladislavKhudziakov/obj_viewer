//
//  EmptyTexture.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef EmptyTexture_hpp
#define EmptyTexture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ITexture.hpp"

namespace Engine {
  class EmptyTexture : public ITexture
  {
    unsigned int texture;
    int width, height;
  public:
    EmptyTexture() : texture(), width(), height() { };
    EmptyTexture(int, int);
    void use(int textureSlot = 0) const override;
    unsigned int get() const override;
  };
}

#endif /* EmptyTexture_hpp */
