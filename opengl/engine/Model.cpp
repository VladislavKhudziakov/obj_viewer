////
////  Model.cpp
////  opengl
////
////  Created by Vladislav Khudiakov on 6/12/19.
////  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
////
//
//#include "Model.hpp"
//
//namespace Engine {
////  class Model
////  {
////  public:
////    Model(const std::string& path)
////    {
////      loadModel(path);
////    }
////    void Draw(Program shader);
////
////    private:
////    std::vector<Mesh> meshes;
////    std::string directory;
////    void loadModel(const std::string& path);
////    void processNode(aiNode *node, const aiScene *scene);
////    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
////    std::vector<tex> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
////  };
//  
//  void Model::loadModel(const std::string& path)
//  {
//    Assimp::Importer import;
//    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//    
//    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//      std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
//      return;
//    }
//    directory = path.substr(0, path.find_last_of('/'));
//    
//    processNode(scene->mRootNode, scene);
//  }
//  
//  void Model::processNode(aiNode *node, const aiScene *scene)
//  {
//    // обработать все полигональные сетки в узле(если есть)
//    for(unsigned int i = 0; i < node->mNumMeshes; i++)
//    {
//      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//      meshes.push_back(processMesh(mesh, scene));
//    }
//    // выполнить ту же обработку и для каждого потомка узла
//    for(unsigned int i = 0; i < node->mNumChildren; i++)
//    {
//      processNode(node->mChildren[i], scene);
//    }
//  }
//}
//
