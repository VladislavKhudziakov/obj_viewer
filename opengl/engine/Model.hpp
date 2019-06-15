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

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "Mesh.hpp"
#include "Program.hpp"

namespace Engine {
  class Model
  {
  private:
    std::vector<Mesh> meshes;
    std::string directoryName;
    std::string fileName;
    std::vector<std::string> loaded_textures;
    
  public:
    Model(const std::string&, const std::string&);
    int loadFromFile(const std::string&);
    void processNodes(const aiNode* node, const aiScene* scene);
    void draw();
    std::vector<std::string> loadMaterialTextures(const aiMesh* mesh, const aiScene* scene, aiTextureType type);
    const std::vector<Mesh>& getMeshes();
  };
}

#endif /* Model_hpp */
