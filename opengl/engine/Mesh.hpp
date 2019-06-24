//
//  Mesh.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/12/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

//#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>

#include "VertexBufferObject.hpp"
#include "Texture.hpp"


namespace Engine
{
  class Mesh
  {
    
  private:
    VBO verticesData;
    Texture texture_diff;
    Texture texture_spec;
    
  public:
    Mesh(const aiMesh* mesh, const aiScene* scene);
    Mesh(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);
    Mesh(const std::vector<float>&, const std::vector<unsigned int>&, const std::vector<float>&, const std::vector<float>&);

    void draw();
    
    const Texture& getDiffTexture() const;
    void setDiffTexture(const Texture&);
    const Texture& getSpecTexture() const;
    void setSpecTexture(const Texture&);
  };
}

#endif /* Mesh_hpp */
