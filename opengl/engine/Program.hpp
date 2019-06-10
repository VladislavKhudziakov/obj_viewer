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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

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
    void set1i(const std::string&, int);
    void set1f(const std::string&, float);
    void setVec3(const std::string&, const glm::vec3&);
    void setMat4(const std::string&, const glm::mat4&);
  };
}

#endif /* Program_hpp */
