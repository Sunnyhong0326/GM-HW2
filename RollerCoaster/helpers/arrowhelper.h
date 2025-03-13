#pragma once

#include "../miscellaneous/shader.h"
#include <Eigen/Dense>

class ArrowHelper {
public:
  ArrowHelper();
  ~ArrowHelper();

  void initialize(Shader *shader);

  void createArrow(float radius = 1.0f, int segments = 16);

  void use(const Eigen::Matrix4f& projectionMatrix, const Eigen::Matrix4f& viewMatrix,
           const Eigen::Vector3f& camPos);
  void setColor(float r, float g, float b);
  void draw(const Eigen::Vector3f& posn, const Eigen::Vector3f& dir, float len, float rad);

private:
  GLuint VAO, VBO, NBO, EBO;
  Shader *shader;
  size_t indicesCount;
};
