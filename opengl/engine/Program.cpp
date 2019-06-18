//
//  Program.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/6/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Program.hpp"


namespace Engine {
  
  Program::Program(const Shader& vShader, const Shader& fShader)
  {
    vertShader = Shader(vShader);
    fragShader = Shader(fShader);
    
    if (!vertShader.isCompiled()) {
      vertShader.compile();
    }
    
    if (!fragShader.isCompiled()) {
      fragShader.compile();
    }
  }
  
  
  Program::Program(const std::string& vShaderPath, const std::string& fShaderPath)
  {
    vertShader = Shader(vShaderPath, GL_VERTEX_SHADER);
    fragShader = Shader(fShaderPath, GL_FRAGMENT_SHADER);
    vertShader.compile();
    fragShader.compile();
  }
  
  
  void Program::link()
  {
    program = glCreateProgram();
    glAttachShader(program, vertShader.get());
    glAttachShader(program, fragShader.get());
    
    glLinkProgram(program);
    
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
      linkedStatus = false;
      return;
    }
    
    linkedStatus = true;
  }
  
  
  void Program::use()
  {
    if (linkedStatus) {
      glUseProgram(program);
    }
  }
  
  
  bool Program::isLinked()
  {
    return linkedStatus;
  }
  
  
  int Program::get()
  {
    return program;
  }
  
  
  void Program::setInt(const std::string& name, int val)
  {
    unsigned int uniform = glGetUniformLocation(program, name.c_str());
    glUniform1i(uniform, val);
  }
  
  
  void Program::setFloat(const std::string& name, float val)
  {
    unsigned int uniform = glGetUniformLocation(program, name.c_str());
    glUniform1f(uniform, val);
  }
  
  
  void Program::setVec3(const std::string& name, const glm::vec3& val)
  {
    unsigned int uniform = glGetUniformLocation(program, name.c_str());
    glUniform3fv(uniform, 1, glm::value_ptr(val));
  }
  
  
  void Program::setMat4(const std::string& name, const glm::mat4& val)
  {
    unsigned int uniform = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(val));
  }
}
