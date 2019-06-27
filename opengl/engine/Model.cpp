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
  Model::Model(const std::string& dirName,
               const std::string& fileName,
               const Program& program)
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
      std::string tex_diff = loadMaterialTexture(mesh, scene, aiTextureType_DIFFUSE);
      std::string tex_spec = loadMaterialTexture(mesh, scene, aiTextureType_SPECULAR);
      std::string tex_ambient = loadMaterialTexture(mesh, scene, aiTextureType_AMBIENT);
      
      Mesh currNodeMesh(mesh, scene);
      
      if (tex_diff.size() > 0) {
        currNodeMesh.setTexture("diffuse", Texture2D(tex_diff, 0));
      }
      
      if (tex_spec.size() > 0) {
        currNodeMesh.setTexture("specular", Texture2D(tex_spec, 1));
      }
      
      if (tex_ambient.size() > 0) {
        currNodeMesh.setTexture("reflection", Texture2D(tex_ambient, 2));
      }
      
      meshes[mesh->mName.C_Str()] = currNodeMesh;
    }
    
    for (int i = 0; i < node->mNumChildren; i++) {
      processNodes(node->mChildren[i], scene);
    }
  }
  
  
  std::string Model::loadMaterialTexture(
    const aiMesh* mesh, const aiScene* scene, aiTextureType type)
  {
    std::string outputTexture;
    
    if(mesh->mMaterialIndex >= 0) {
      const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      
      int texCount = material->GetTextureCount(type);
      
      if (texCount > 0) {
        aiString path;
        material->GetTexture(type, 0, &path);
        
        std::string full_path(path.C_Str());
        full_path = directoryName + full_path;
        
        outputTexture = full_path;
      }
    }
    
    return outputTexture;
  }
  
  
  void Model::draw()
  {
    shaderProgram.use();
    
    for(auto mesh : meshes) {
      const std::map<std::string, Texture2D>& meshTextures = mesh.second.getTextures();
      
      const std::string materialTemplate = "material.";
      
      int currTexId = 0;
      for (auto keyValuePair : meshTextures) 
        keyValuePair.second.use(currTexId);
        shaderProgram.setInt(materialTemplate + keyValuePair.first, currTexId);
        currTexId++;
      }
      
      currTexId++;
      envTex.use(currTexId);
      shaderProgram.setInt("skyboxTexure", currTexId);
      
      mesh.second.draw();
    }
  }
  
  
  std::map<std::string, Mesh>& Model::getMeshes()
  {
    return meshes;
  }
  
  void Model::setEnvTex(const CubemapTexture& tex)
  {
    envTex = tex;
  }
}
