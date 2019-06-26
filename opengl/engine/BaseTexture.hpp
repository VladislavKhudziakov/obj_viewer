//
//  BaseTexture.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/26/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef BaseTexture_hpp
#define BaseTexture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ITexture.hpp"

namespace Engine {
  class BaseTexture: public ITexture
  {
  protected:
    unsigned int texture;
    int texID;
    
  public:
    BaseTexture(int textureSlot = 0);
    virtual int getID() override;
    virtual unsigned int get() override;
  };
}
#endif /* BaseTexture_hpp */
