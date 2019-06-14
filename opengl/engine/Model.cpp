////
////  Model.cpp
////  opengl
////
////  Created by Vladislav Khudiakov on 6/12/19.
////  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
////
//

#include "Model.hpp"

namespace Engine
{  
  Model::Model(const std::string& fileName)
  {
    loadFromFile(fileName);
  }
  
  
  int Model::loadFromFile(const std::string& fileName)
  {
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(
     fileName.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
      return -1;
    }
    
    const aiNode* rootNode = scene->mRootNode;
    
    processNodes(rootNode, scene);
    
    return 0;
  }
  
  
  void Model::processNodes(const aiNode* node, const aiScene* scene)
  {
    for (int i = 0; i < node->mNumMeshes; i++) {
      const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(Mesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
      processNodes(node->mChildren[i], scene);
    }
  }
  
  
  void Model::draw()
  {
    for (auto mesh : meshes) {
      mesh.draw();
    }
  }
  
  
  const std::vector<Mesh>& Model::getMeshes()
  {
    return meshes;
  }
}
