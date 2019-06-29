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
#include <map>
#include <iostream>

#include "IDrawable.hpp"
#include "VertexBufferObject.hpp"
#include "Texture.hpp"


namespace Engine
{
  class Mesh : public IDrawable
  {
    
  private:
    VBO verticesData;
    std::map<std::string, Texture2D> textures;
    
  public:
    Mesh() : IDrawable() { };
    Mesh(const aiMesh* mesh, const aiScene* scene);
    Mesh(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);
    Mesh(const std::vector<float>&, const std::vector<unsigned int>&, const std::vector<float>&, const std::vector<float>&);

    void draw() const;
    
    void setTexture(const std::string&,const Texture2D&);
    const std::map<std::string, Texture2D>& getTextures();
  };
}

#endif /* Mesh_hpp */
