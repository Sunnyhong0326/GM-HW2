#pragma once
#include "../miscellaneous/shader.h"
#include <Eigen/Dense>

class VertexHelper {
public:
  VertexHelper();
  ~VertexHelper();

  void initialize(Shader* sphere_shader);
  void use(const Eigen::Matrix4f& projectionMatrix, const Eigen::Matrix4f& viewMatrix,
           const Eigen::Vector3f& camPos);
  void draw(const Eigen::Vector3f &translation, bool selected);
private:
  // OpenGL buffers
  unsigned int VAO, VBO, EBO;
  size_t vertexCount;
  size_t indicesCount;

  // Axis buffers
  unsigned int axisVAO, axisVBO, axisCBO;

  Shader *sphereShader;

  void createSphere(float radius, int segments, int rings,
                    unsigned int& vao, unsigned int& vbo, unsigned int& ebo,
                    size_t& v_count, size_t& i_count);
};
