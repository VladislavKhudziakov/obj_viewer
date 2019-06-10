//
//  Program.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/6/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include "Shader.hpp"

namespace Engine {
  class Program
  {
    Shader vertShader;
    Shader fragShader;
    int program;
    bool linkedStatus;
    
  public:
    Program(const Shader& vShader, const Shader& fShader);
    Program(const std::string& vShaderPath, const std::string& fShaderPath);
    void link();
    void use();
    bool isLinked();
    int get();
    void set1i();
    void set1f();
    void setVec3();
    void setMat4();
  };
}

#endif /* Program_hpp */
