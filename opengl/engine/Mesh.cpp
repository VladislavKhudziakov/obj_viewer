//
//  Mesh.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/12/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Mesh.hpp"

namespace Engine
{  
  Mesh::Mesh(const aiMesh* mesh, const aiScene* scene)
  {
    std::vector<float> positions;
    std::vector<unsigned int> indices;
    std::vector<float> uv;
    std::vector<float> normals;
    
    for (int i = 0; i < mesh->mNumVertices; i++) {
      if (mesh->HasPositions()) {
        positions.push_back(mesh->mVertices[i].x);
        positions.push_back(mesh->mVertices[i].y);
        positions.push_back(mesh->mVertices[i].z);
      }
      
      if(mesh->HasNormals()) {
        normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);
      }
      
      if(mesh->HasTextureCoords(0)) {
        uv.push_back(mesh->mTextureCoords[0][i].x);
        uv.push_back(mesh->mTextureCoords[0][i].y);
      }
    }
    
    for (int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (int j = 0; j < face.mNumIndices; j++) {
        indices.push_back(face.mIndices[j]);
      }
    }
    
    verticesData = VBO(positions, indices, normals, uv);
  }
  
  
  void Mesh::draw()
  {
    verticesData.draw();
  }
  
  
  const Texture& Mesh::getDiffTexture() const
  {
    return texture_diff;
  }
  
  
  void Mesh::setDiffTexture(const Texture& new_diff_tex)
  {
    texture_diff = new_diff_tex;
  }
  
  
  const Texture& Mesh::getSpecTexture() const
  {
    return texture_spec;
  }
  
  
  void Mesh::setSpecTexture(const Texture& new_spec_tex)
  {
    texture_spec = new_spec_tex;
  }
}
