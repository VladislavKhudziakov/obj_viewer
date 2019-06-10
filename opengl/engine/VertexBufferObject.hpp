//
//  VertexBufferObject.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/7/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef VertexBufferObject_hpp
#define VertexBufferObject_hpp

#include <initializer_list>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "bufferData.hpp"

namespace Engine {
  class VBO
  {
  private:
    unsigned int vao;
    unsigned int vertBuffer;
    unsigned int uvBuffer;
    unsigned int normalsBuffer;
    
    int vertBufferSize;
    
  public:
    VBO(float vertices[], int vertSize, float uv[] = nullptr, int uvSize = 0, float normals[] = nullptr, int normalsSize = 0);
    
    void use();
    void unUse();
    void del();
    void draw();
    int getVAO() const noexcept;
  };
}


#endif /* VertexBufferObject_hpp */
