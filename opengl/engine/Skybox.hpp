//
//  Skybox.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/25/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <string>
#include <vector>

#include "IDrawable.hpp"
#include "CubemapTexture.hpp"
#include "Program.hpp"
#include "VertexBufferObject.hpp"

namespace Engine {
  class Skybox : public IDrawable
  {
  private:
    CubemapTexture texture;
    Program shaderProgram;
    VBO vertices;
    
    std::vector<float> getVBOVertivces();
    
  public:
    Skybox() : texture(), shaderProgram() { };
    const CubemapTexture& getTexture();
    Skybox(const std::vector<std::string>&, const Program& );
    void draw() const override;
  };
}
#endif /* Skybox_hpp */
