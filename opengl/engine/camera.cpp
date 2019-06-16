//
//  camera.cpp
//  opengl
//
//  Created by Vladislav Khudiakov on 6/9/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "camera.hpp"

namespace Engine
{
  
  Camera::Camera(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up)
  {
    position = pos;
    direction = dir;
    this->up = up;
    
    view = glm::lookAt(position, direction, this->up);
  }
  
  
  const glm::mat4& Camera::getView() const noexcept
  {
    return view;
  }
  
  
  void Camera::setPosition(const glm::vec3& newPosition)
  {
    position = newPosition;
  }
  
  
  const glm::vec3& Camera::getPosition()
  {
    return position;
  }
  
  
  void Camera::setDirection(const glm::vec3& newDirection)
  {
    direction = newDirection;
  }
  
  
  const glm::vec3& Camera::getDirection()
  {
    return direction;
  }
  
  
  void Camera::setUp(const glm::vec3& newUp)
  {
    up = newUp;
  }
  
  
  const glm::vec3& Camera::getUp()
  {
    return up;
  }
  
  
  void Camera::computeView(const glm::vec3& newPos, const glm::vec3& newDir, const glm::vec3& newUp)
  {
    position = newPos;
    direction = newDir;
    up = newUp;
    view = glm::lookAt(position, direction, up);
  }
  
  
  void Camera::computeView()
  {
    view = glm::lookAt(position, direction, up);
  }
}
