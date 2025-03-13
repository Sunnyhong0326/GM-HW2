#include "BoxHelper.h"
#include <glad/glad.h>

BoxHelper::BoxHelper() : shader(nullptr), VAO(0), VBO(0), EBO(0) {}

BoxHelper::~BoxHelper() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void BoxHelper::initialize(Shader *boxShader) {
  shader = boxShader;
  setupBuffers();
}

void BoxHelper::setupBuffers() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
  // Define vertices for a unit cube centered at origin
  vertices = {// positions          // normals          // colors
              -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.5f,  0.0f, // orange
              0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.5f,  0.0f,  0.5f,  0.5f,  -0.5f,
              0.0f,  0.0f,  -1.0f, 1.0f,  0.5f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
              1.0f,  0.5f,  0.0f,

              -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.7f,  0.2f,  0.5f,  -0.5f, 0.5f,
              0.0f,  0.0f,  1.0f,  1.0f,  0.7f,  0.2f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
              1.0f,  0.7f,  0.2f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.7f,  0.2f,

              -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  0.8f,  0.4f,  0.0f,  -0.5f, 0.5f,  -0.5f,
              -1.0f, 0.0f,  0.0f,  0.8f,  0.4f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
              0.8f,  0.4f,  0.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.8f,  0.4f,  0.0f,

              0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.6f,  0.1f,  0.5f,  0.5f,  -0.5f,
              1.0f,  0.0f,  0.0f,  1.0f,  0.6f,  0.1f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
              1.0f,  0.6f,  0.1f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.6f,  0.1f,

              -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.9f,  0.5f,  0.1f,  0.5f,  -0.5f, -0.5f,
              0.0f,  -1.0f, 0.0f,  0.9f,  0.5f,  0.1f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
              0.9f,  0.5f,  0.1f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.9f,  0.5f,  0.1f,

              -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.6f,  0.2f,  0.5f,  0.5f,  -0.5f,
              0.0f,  1.0f,  0.0f,  1.0f,  0.6f,  0.2f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
              1.0f,  0.6f,  0.2f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.6f,  0.2f};

  // Define indices for the cube faces
  indices = {
      0,  1,  2,  2,  3,  0,  // Front face
      4,  5,  6,  6,  7,  4,  // Back face
      8,  9,  10, 10, 11, 8,  // Left face
      12, 13, 14, 14, 15, 12, // Right face
      16, 17, 18, 18, 19, 16, // Bottom face
      20, 21, 22, 22, 23, 20  // Top face
  };
  indicesCount = indices.size();

  // Generate buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind VAO
  glBindVertexArray(VAO);

  // Set up VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  // Set up EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),
               GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Color attribute
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Unbind
  glBindVertexArray(0);
}

void BoxHelper::use(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& view, const Eigen::Vector3f& camPos)
{
    shader->use();
    shader->setMat4("projection_matrix", projection);
    shader->setMat4("view_matrix", view);
    shader->setVec3("viewPos", camPos);
}

void BoxHelper::draw(const Eigen::Vector3f &p, const Eigen::Vector3f &t, const Eigen::Vector3f& n, float scale) {
  if (!shader)
    return;

  Eigen::Vector3f b = t.cross(n);
  Eigen::Matrix4f model;
  model << scale * t.x(), scale * n.x(), scale * b.x(), p.x(),
           scale * t.y(), scale * n.y(), scale * b.y(), p.y(),
           scale * t.z(), scale * n.z(), scale * b.z(), p.z(),
      0.0f, 0.0f, 0.0f, 1.0f;
  shader->setMat4("model_matrix", model);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indicesCount), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
