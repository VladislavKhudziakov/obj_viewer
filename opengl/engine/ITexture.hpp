//
//  ITexture.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/26/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef ITexture_hpp
#define ITexture_hpp

namespace Engine {
  class ITexture
  {
  public:
    virtual ~ITexture() { };
    virtual void use() = 0;
    virtual void use(int) = 0;
    virtual int getID() = 0;
    virtual unsigned int get() = 0;
  };
}
#endif /* ITexture_hpp */
