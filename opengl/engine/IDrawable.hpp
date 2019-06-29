//
//  IDrawable.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/29/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef IDrawable_hpp
#define IDrawable_hpp

namespace Engine
{
  class IDrawable
  {
  public:
    virtual ~IDrawable() { };
    virtual void draw() const = 0;
  };
}
#endif /* IDrawable_hpp */
