//
//  Mesh.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/12/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "VertexBufferObject.hpp"

namespace Engine
{
  class Mesh
  {
    
  private:
    VBO verticesData;
    
  public:
    Mesh(aiMesh* mesh);
    void draw();
  };
}

#endif /* Mesh_hpp */
