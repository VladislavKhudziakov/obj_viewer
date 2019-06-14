//
//  Model.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/12/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

namespace Engine {
  class Model
  {
  public:
    Model(const std::string& path)
    {
      loadModel(path);
    }
    void Draw(Program shader);
    
  private:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<tex> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
  };
}

#endif /* Model_hpp */
