//
//  camera.hpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
  class Camera
  {
  private:
    glm::mat4 view;
    
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    
  public:
    Camera(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up);
    const glm::mat4& getView() const noexcept;
    
    void setPosition(const glm::vec3&);
    const glm::vec3& getPosition();
    void setDirection(const glm::vec3&);
    const glm::vec3& getDirection();
    void setUp(const glm::vec3&);
    const glm::vec3& getUp();
    
    void computeView(const glm::vec3&, const glm::vec3&, const glm::vec3&);
    void computeView();
  };
}

#endif /* camera_hpp */
