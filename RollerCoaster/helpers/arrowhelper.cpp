#include "arrowhelper.h"
#define M_PI 3.14159265358979323846

ArrowHelper::ArrowHelper() : VAO(0), VBO(0), NBO(0), EBO(0), indicesCount(0), shader(nullptr) {}

ArrowHelper::~ArrowHelper() {
  if (VAO)
    glDeleteVertexArrays(1, &VAO);
  if (VBO)
    glDeleteBuffers(1, &VBO);
  if (NBO)
    glDeleteBuffers(1, &NBO);
  if (EBO)
    glDeleteBuffers(1, &EBO);
}

void ArrowHelper::initialize(Shader *shader) { 
    this->shader = shader; 
    createArrow();
}

void ArrowHelper::createArrow(float radius, int segments) {
  if (VAO)
    glDeleteVertexArrays(1, &VAO);
  if (VBO)
    glDeleteBuffers(1, &VBO);
  if (NBO)
    glDeleteBuffers(1, &NBO);
  if (EBO)
    glDeleteBuffers(1, &EBO);

  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<unsigned int> indices;

  Eigen::Vector3f lx(1.0f, 0.0f, 0.0f);
  Eigen::Vector3f ly(0.0f, 1.0f, 0.0f);
  Eigen::Vector3f lz(0.0f, 0.0f, 1.0f);

  float rad[] = {radius, radius, 2.0f * radius};
  float t[] = {0.0f, 0.7f, 0.7f};

  for (int i = 0; i < 3; i++) {
    Eigen::Vector3f offset = lx * t[i];

    for (int j = 0; j < segments; j++) {
      float theta = 2.0f * M_PI * float(j) / float(segments);

      Eigen::Vector3f pt = cos(theta) * ly * rad[i] + sin(theta) * lz * rad[i];
      vertices.push_back(offset.x() + pt.x());
      vertices.push_back(offset.y() + pt.y());
      vertices.push_back(offset.z() + pt.z());

      pt = pt.normalized();
      normals.push_back(pt[0]);
      normals.push_back(pt[1]);
      normals.push_back(pt[2]);
    }
  }

  // Indices
  for (int i = 1; i < 3; i++) {
    for (int j = 0; j < segments; j++) {
      int p0 = (i - 1) * segments + (j - 1 + segments) % segments;
      int p1 = (i - 1) * segments + j;
      int p2 = i * segments + (j - 1 + segments) % segments;
      int p3 = i * segments + j;

      indices.push_back(p1);
      indices.push_back(p0);
      indices.push_back(p2);

      indices.push_back(p1);
      indices.push_back(p2);
      indices.push_back(p3);
    }
  }

  // Create circle
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);
  //
  vertices.push_back(1.0f);
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);
  //
  normals.push_back(-lx[0]);
  normals.push_back(-lx[1]);
  normals.push_back(-lx[2]);
  //
  normals.push_back(lx[0]);
  normals.push_back(lx[1]);
  normals.push_back(lx[2]);
  // Set Indices
  for (int i = 0; i < segments; i++) {
    indices.push_back(i);
    indices.push_back((i + 1) % segments);
    indices.push_back(segments * 3);

    indices.push_back(segments * 2 + i);
    indices.push_back(segments * 2 + ((i + 1) % segments));
    indices.push_back(segments * 3 + 1);
  }

  // Setup VAO, VBO, NBO, EBO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &NBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, NBO);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),
               GL_STATIC_DRAW);

  glBindVertexArray(0);

  indicesCount = indices.size();
}

void ArrowHelper::use(const Eigen::Matrix4f& projectionMatrix, const Eigen::Matrix4f& viewMatrix, const Eigen::Vector3f& camPos)
{
    shader->use();
    shader->setMat4("projection_matrix", projectionMatrix);
    shader->setMat4("view_matrix", viewMatrix);
    shader->setVec3("viewPos", camPos);
}

void ArrowHelper::setColor(float r, float g, float b)
{
    shader->setVec3("color", r, g, b);
}

void ArrowHelper::draw(const Eigen::Vector3f& posn, const Eigen::Vector3f& dir, float len, float rad)
{
    Eigen::Vector3f lx = dir;
    lx.normalize();
    Eigen::Vector3f ly(0.0f, 1.0f, 0.0f);
    if (1.0f - abs(lx.dot(ly)) < 1e-6) { ly << 0.0f, 0.0f, 1.0f; }
    Eigen::Vector3f lz = lx.cross(ly);
    lz.normalize();
    ly = lx.cross(lz);
    ly.normalize();
    //rendering
    Eigen::Matrix4f model;
    model << len * lx.x(), rad * ly.x(), rad * lz.x(), posn.x(),
             len * lx.y(), rad * ly.y(), rad * lz.y(), posn.y(),
             len * lx.z(), rad * ly.z(), rad * lz.z(), posn.z(),
        0.0f, 0.0f, 0.0f, 1.0f;
    shader->setMat4("model_matrix", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indicesCount, GL_UNSIGNED_INT, 0);
}