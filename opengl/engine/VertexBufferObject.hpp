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
    unsigned int ebo;
    unsigned int vertBuffer;
    unsigned int elBufferSize;
    unsigned int uvBuffer;
    unsigned int normalsBuffer;
    
    int vertBufferSize;
    
  public:
    VBO() { };
    
    VBO(const std::vector<float>& vertices,
        const std::vector<float>& normals,
        const std::vector<float>& uv);
    
    VBO(const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<float>& normals,
        const std::vector<float>& uv);
    
    void set();
    void unSet();
    void del();
    void draw();
    int getVAO() const noexcept;
  };
}


#endif /* VertexBufferObject_hpp */
