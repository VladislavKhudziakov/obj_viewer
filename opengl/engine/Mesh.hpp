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
    std::vector<Texture> textures_diff;
    std::vector<Texture> textures_spec;
    
    void loadMaterialTextures(const aiMaterial*, aiTextureType);
    
  public:
    Mesh(const aiMesh* mesh, const aiScene* scene);
    void draw();
    
    const std::vector<Texture>& getTexturesList(const std::string&) const;
  };
}

#endif /* Mesh_hpp */
