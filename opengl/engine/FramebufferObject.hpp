//
//  FramebufferObject.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef FramebufferObject_hpp
#define FramebufferObject_hpp

#include <iostream>

#include "ITexture.hpp"
#include "RenderbufferObject.hpp"

namespace Engine
{
  class FBO
  {
    unsigned int fbo;
  public:
    FBO();
    void attachColorbuffer(const ITexture& );
    void attachRenderbuffer(const RBO& );
    void use() const;
    void unuse() const;
    unsigned int get() const;
    void checkStatus();
  };
}
#endif /* FramebufferObject_hpp */
