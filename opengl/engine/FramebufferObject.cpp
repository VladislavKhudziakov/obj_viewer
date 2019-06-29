//
//  FramebufferObject.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "FramebufferObject.hpp"

namespace Engine
{
//  class FBO
//  {
//    unsigned int fbo;
//  public:
//    FBO();
//    void attachColorbuffer(const ITexture& );
//    void attachRenderbuffer(const RBO& );
//    void use() const;
//    void unuse() const;
//  };
  
  FBO::FBO()
  {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  
  void FBO::use() const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  }
  
  
  void FBO::unuse() const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  
  
  void FBO::attachColorbuffer(const ITexture& colorbuffer)
  {
    use();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuffer.get(), 0);
    unuse();
  }
  
  
  void FBO::attachRenderbuffer(const RBO& renderbuffer)
  {
    use();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.get());
    unuse();
  }
  
  void FBO::checkStatus()
  {
    use();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    unuse();
  }
}
