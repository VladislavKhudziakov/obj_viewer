//
//  Shader.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/6/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Shader.hpp"

namespace Engine {
  
  Shader::Shader(const Shader& src)
  {
    type = src.type;
    source = src.source;
    path = src.path;
    shader = src.shader;
    compiledStatus = src.compiledStatus;
  }
  
  
  Shader::Shader(GLenum type)
  {
    compiledStatus = false;
    if (type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER) {
      this->type = type;
      source = "\0";
      path = "\0";
    } else {
      std::cout << "ERROR::SHADER::INVALID_TYPE\n";
    }
  }
  
  
  Shader::Shader(std::string path, GLenum type)
  {
    compiledStatus = false;
    if (type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER) {
      this->type = type;
      LoadFromFile(path);
    } else {
      std::cout << "ERROR::SHADER::INVALID_TYPE\n";
    }
  }
  
  
  void Shader::LoadFromFile(std::string path)
  {
    path = path;
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);
    try {
      file.open(path);
      std::stringstream fileSource;
      fileSource << file.rdbuf();
      source = fileSource.str();
    } catch (std::ifstream::failure err) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
  }
  
  
  int Shader::compile()
  {
    if (source != "\0") {
      shader = glCreateShader(type);
      const char* shaderCode = source.c_str();
      glShaderSource(shader, 1, &shaderCode, NULL);
      glCompileShader(shader);
      
      int success;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      
      if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string errMsg;
        
        if (type == GL_VERTEX_SHADER) {
          errMsg = "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n";
        } else if (type == GL_FRAGMENT_SHADER) {
          errMsg = "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n";
        }
        
        std::cout << errMsg << infoLog << std::endl;
        
        compiledStatus = false;
        return -1;
      }
      
      compiledStatus = true;
      return 0;
    }
    
    compiledStatus = false;
    return -1;
  }
  
  
  const std::string& Shader::getSource() const noexcept
  {
    return source;
  }
  
  
  const std::string& Shader::getPath() const noexcept
  {
    return path;
  }
  
  
  int Shader::get() const noexcept
  {
    return shader;
  }
  
  
  bool Shader::isCompiled() const noexcept
  {
    return compiledStatus;
  }
}
