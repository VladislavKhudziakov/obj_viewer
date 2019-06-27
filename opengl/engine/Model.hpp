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
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

#include "Mesh.hpp"
#include "Program.hpp"
#include "CubemapTexture.hpp"

namespace Engine {
  class Model
  {
  private:
    Program shaderProgram;
    std::string directoryName;
    std::string fileName;
    std::map<std::string, Mesh> meshes;
    CubemapTexture envTex;
    
  public:
    Model(const std::string&, const std::string&, const Program&);
    int loadFromFile(const std::string&);
    void processNodes(const aiNode* node, const aiScene* scene);
    void draw();
    std::string loadMaterialTexture(const aiMesh* mesh, const aiScene* scene, aiTextureType type);
    std::map<std::string, Mesh>& getMeshes();
    void setEnvTex(const CubemapTexture&);
  };
}

#endif /* Model_hpp */
