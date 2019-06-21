//
//  constants.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/16/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef constants_hpp
#define constants_hpp

namespace Engine {
  enum {
    CULL_FACING_FRONT,
    CULL_FACING_BACK
  };
  
  enum {
    BLENDING_SCREEN,
    BLENDING_ALPHA,
    BLENDING_MULTIPLY,
    BLENDING_ADD
  };
  
  enum {
    FRAMEBUFFER_DEPTH_TEST_ACTIVATE = 1,
    FRAMEBUFFER_CLEAR_COLOR = 2,
  };
}

#endif /* constants_hpp */
