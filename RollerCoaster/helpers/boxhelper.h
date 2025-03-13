#ifndef BOX_HELPER_H
#define BOX_HELPER_H

#include "../miscellaneous/shader.h"

class BoxHelper {
public:
  BoxHelper();
  ~BoxHelper();

  void initialize(Shader *boxShader);
  void use(const Eigen::Matrix4f& projectionMatrix, const Eigen::Matrix4f& viewMatrix,
           const Eigen::Vector3f& camPos);
  void draw(const Eigen::Vector3f &position, const Eigen::Vector3f &tangent, const Eigen::Vector3f& normal, float scale = 1.0f);

private:
  void setupBuffers();

  Shader *shader;
  unsigned int VAO, VBO, EBO;
  size_t indicesCount;
};

#endif // BOX_HELPER_H
