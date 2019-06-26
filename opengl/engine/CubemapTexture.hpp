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

#include "BaseTexture.hpp"

namespace Engine {
  class CubemapTexture : public BaseTexture
  {
  public:
    CubemapTexture() : BaseTexture() { };
    CubemapTexture(const std::vector<std::string>&, int texSlot = 0);
    virtual void use() const override;
    virtual void use(int) const override;
  };
}
#endif /* CubemapTexture_hpp */
