//
//  Framebuffer.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/21/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp

namespace Engine {
  class Framebuffer
  {
  private:
    unsigned int colorbuffer;
    unsigned int renderbuffer;
    unsigned int framebuffer;
    
  public:
    Framebuffer(unsigned int, unsigned int, unsigned int);
    unsigned int getColorbuffer();
    unsigned int getRenderbuffer();
    unsigned int get();
  };
}
#endif /* Framebuffer_hpp */
