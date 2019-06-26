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
    ITexture() { };
    virtual ~ITexture() { };
    virtual void use() const = 0;
    virtual void use(int) const = 0;
    virtual int getID() const = 0;
    virtual unsigned int get() const = 0;
  };
}
#endif /* ITexture_hpp */
