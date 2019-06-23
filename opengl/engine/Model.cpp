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
      std::string tex_diff = loadMaterialTexture(mesh, scene, aiTextureType_DIFFUSE);
      std::string tex_spec = loadMaterialTexture(mesh, scene, aiTextureType_SPECULAR);
      
      Mesh node_mesh(mesh, scene);

      if (tex_diff.size() > 0) {
          loaded_textures.push_back(tex_diff);
          int tex_idx = static_cast<int>(loaded_textures.size());
          node_mesh.setDiffTexture(Texture(tex_diff, tex_idx));
      }

      if (tex_spec.size() > 0) {
          loaded_textures.push_back(tex_spec);
          int tex_idx = static_cast<int>(loaded_textures.size());
          node_mesh.setSpecTexture(Texture(tex_spec, tex_idx));
      }
      
      meshes.push_back(node_mesh);
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
    
    for (auto mesh : meshes) {
      
      auto mesh_diff_tex = mesh.getDiffTexture();
      
      int tex_diff_slot = mesh_diff_tex.get();
      if (tex_diff_slot < 32) {
        mesh_diff_tex.use();
        shaderProgram.setInt("material.diffuse", 0);
      }
      
      auto mesh_spec_tex = mesh.getSpecTexture();
      
      int tex_spec_slot = mesh_spec_tex.get();
      if (tex_spec_slot < 32) {
        mesh_spec_tex.use();
        shaderProgram.setInt("material.specular", 1);
      }
      
      mesh.draw();
    }
  }
  
  
  const std::vector<Mesh>& Model::getMeshes()
  {
    return meshes;
  }
}
