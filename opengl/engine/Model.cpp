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
  Model::Model(
   const std::string& dirName, const std::string& fileName, const Program& program)
  {
    this->directoryName = dirName;
    this->fileName = fileName;
    this->shaderProgram = program;
    
    if (loadFromFile(dirName + fileName) < 0) {
      std::cout << "MODEL::LOAD_FROM_FILE::ERROR\n";
    }
  }
  
  
  int Model::loadFromFile(const std::string& fileName)
  {
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(
     fileName.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
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
      auto tex_diff = loadMaterialTextures(mesh, scene, aiTextureType_DIFFUSE);
      auto tex_spec = loadMaterialTextures(mesh, scene, aiTextureType_SPECULAR);
      
      Mesh node_mesh(mesh, scene);

      if (tex_diff.size() > 0) {
          node_mesh.setDiffTexture(Texture(tex_diff[0]));
      }

      if (tex_spec.size() > 0) {
          node_mesh.setSpecTexture(Texture(tex_spec[0]));
      }
      
      meshes.push_back(node_mesh);
    }
    
    for (int i = 0; i < node->mNumChildren; i++) {
      processNodes(node->mChildren[i], scene);
    }
  }
  
  
  std::vector<std::string> Model::loadMaterialTextures(
    const aiMesh* mesh, const aiScene* scene, aiTextureType type)
  {
    std::vector<std::string> outputTextures;
    
    if(mesh->mMaterialIndex >= 0) {
      const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      
      int texCount = material->GetTextureCount(type);
      
      for (int i = 0; i < texCount; i++) {
        aiString path;
        material->GetTexture(type, i, &path);
        
        std::string full_path(path.C_Str());
        full_path = directoryName + full_path;
        
        outputTextures.push_back(full_path);
        
        auto founded_element = std::find(
          loaded_textures.begin(), loaded_textures.end(), full_path);
        
        if (founded_element == loaded_textures.end()) {
          loaded_textures.push_back(full_path);
        }
      }
    }
    
    return outputTextures;
  }
  
  
  void Model::draw()
  {
    shaderProgram.use();
    
    for (auto mesh : meshes) {
      
      if (mesh.getDiffTexture().getSlot() < 32) {
        shaderProgram.setInt("material.diffuse", mesh.getDiffTexture().getSlot());
      }
      
      if (mesh.getSpecTexture().getSlot() < 32) {
        shaderProgram.setInt("material.specular", mesh.getSpecTexture().getSlot());
      }
      
      mesh.draw();
    }
  }
  
  
  const std::vector<Mesh>& Model::getMeshes()
  {
    return meshes;
  }
}
