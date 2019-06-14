//
//  Vertex.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/12/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <glm/glm.hpp>

namespace Engine {
  struct Vertex {
    glm::vec3 Positiom;
    glm::vec3 Normal;
    glm::vec3 UV;
  };
}

#endif /* Vertex_hpp */
