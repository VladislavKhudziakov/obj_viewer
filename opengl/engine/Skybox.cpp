//
//  Skybox.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/25/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Skybox.hpp"

namespace Engine {
  
  Skybox::Skybox(const std::vector<std::string>& textures,
                 const Program& shaderProgram)
  {
    this->shaderProgram = shaderProgram;
    vertices = VBO(getVBOVertivces(), std::vector<float>(1.), std::vector<float>(1.));
    texture = CubemapTexture(textures);
  }
  
  
  const CubemapTexture& Skybox::getTexture()
  {
    return texture;
  }
  
  
  void Skybox::draw()
  {
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    texture.use();
    shaderProgram.setInt("skybox", 0);
    vertices.draw();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
  }
  
  
  std::vector<float> Skybox::getVBOVertivces()
  {
    std::vector<float> vertices {
      -1.0f,  1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      
      -1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,
      
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      
      -1.0f, -1.0f,  1.0f,
      -1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,
      
      -1.0f,  1.0f, -1.0f,
       1.0f,  1.0f, -1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f, -1.0f,
      
      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
       1.0f, -1.0f,  1.0f
    };
    
    return vertices;
  }
}
