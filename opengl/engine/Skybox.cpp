//
//  Skybox.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/25/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Skybox.hpp"

namespace Engine {
  
  Skybox::Skybox(const std::string& dirName,
                 const std::vector<std::string>& textures,
                 const Program& shaderProgram)
  {
    this->shaderProgram = shaderProgram;
    vertices = VBO(getVBOVertivces(), std::vector<float>(1.), std::vector<float>(1.));
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    
    unsigned int i = 0;
    
    for (auto currTex : textures) {
      int width, height;
      
      unsigned char* imgData = SOIL_load_image(
       (dirName + currTex).c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
      
      if (imgData) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
          0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
      } else {
        std::cout << "Cubemap texture failed to load at path: " << dirName + currTex << std::endl;
      }
      
      i++;
      
      SOIL_free_image_data(imgData);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  }
  
  
  void Skybox::draw()
  {
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
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
