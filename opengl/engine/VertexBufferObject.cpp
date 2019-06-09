//
//  VertexBufferObject.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/7/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "VertexBufferObject.hpp"

namespace Engine {
  
  VBO::VBO(float vertices[], int vertSize, float uv[], int uvSize)
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  
    glGenBuffers(1, &vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvSize, uv, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    vertBufferSize = vertSize;
  }
  
  
  void VBO::use()
  {
    glBindVertexArray(vao);
  }
  
  
  void VBO::unUse()
  {
    glBindVertexArray(0);
  }
  
  
  void VBO::draw()
  {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertBufferSize / sizeof(float));
    glBindVertexArray(0);
  }
  
  
  int VBO::getVAO() const noexcept
  {
    return vao;
  }
  
  void VBO::del()
  {
    glDeleteBuffers(1, &vertBuffer);
    glDeleteBuffers(1, &uvBuffer);
  }
  
}
