//
//  CubemapTexture.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/26/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef CubemapTexture_hpp
#define CubemapTexture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <iostream>
#include <string>
#include <vector>

#include "ITexture.hpp"

namespace Engine {
  class CubemapTexture : public ITexture
  {
    unsigned int texture;
  public:
    CubemapTexture() : ITexture(), texture() { };
    CubemapTexture(const std::vector<std::string>&, int texSlot = 0);
    void use(int textureSlot = 0) const override;
    unsigned int get() const override;
  };
}
#endif /* CubemapTexture_hpp */
