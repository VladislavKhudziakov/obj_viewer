//
//  Shader.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/6/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine {
  class Shader
  {
  private:
    std::string source;
    std::string path;
    GLenum type;
    int shader;
    bool compiledStatus;
    
  public:
    Shader() { };
    Shader(const Shader&);
    Shader(GLenum type);
    Shader(std::string path, GLenum type);
    const std::string& getSource() const noexcept;
    const std::string& getPath() const noexcept;
    void LoadFromFile(std::string path);
    int compile();
    bool isCompiled() const noexcept;
    int get() const noexcept;
  };
}

#endif /* Shader_hpp */
