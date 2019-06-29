//
//  VertexBufferObject.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/7/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "VertexBufferObject.hpp"

namespace Engine {
  
  VBO::VBO(const std::vector<float>& vertices,
           const std::vector<float>& normals,
           const std::vector<float>& uv)
    : IDrawable(), ebo()
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    int vertBufferSize = static_cast<int>(vertices.size() * sizeof(float));
    glGenBuffers(1, &vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertBufferSize, &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    int uvBufferSize = static_cast<int>(uv.size() * sizeof(float));
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvBufferSize, &uv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    int normBufferSize = static_cast<int>(normals.size() * sizeof(float));
    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normBufferSize, &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->vertBufferSize = vertBufferSize;
  }
  
  VBO::VBO(const std::vector<float>& vertices,
      const std::vector<unsigned int>& indices,
      const std::vector<float>& normals,
      const std::vector<float>& uv)
    : IDrawable()
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    int indecesBufferSize = static_cast<int>(indices.size() * sizeof(unsigned int));
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecesBufferSize, &indices[0], GL_STATIC_DRAW);
    
    int vertBufferSize = static_cast<int>(vertices.size() * sizeof(float));
    glGenBuffers(1, &vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertBufferSize, &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    int uvBufferSize = static_cast<int>(uv.size() * sizeof(float));
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvBufferSize, &uv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    int normBufferSize = static_cast<int>(normals.size() * sizeof(float));
    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normBufferSize, &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->vertBufferSize = vertBufferSize;
    elBufferSize = indecesBufferSize;
  }
  
  
  void VBO::set()
  {
    glBindVertexArray(vao);
    if (ebo) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    }
  }
  
  
  void VBO::unSet()
  {
    glBindVertexArray(0);
  }
  
  
  void VBO::draw() const
  {
    glBindVertexArray(vao);
    if (ebo) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glDrawElements(GL_TRIANGLES, elBufferSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    } else {
      glDrawArrays(GL_TRIANGLES, 0, vertBufferSize / sizeof(float));
    }
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
