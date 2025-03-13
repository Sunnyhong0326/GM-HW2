#include "CurveRenderer.h"
#include "CurveProcessor.h"

#define M_PI 3.14159265358979323846

CurveRenderer::CurveRenderer() : VAO(0), VBO(0), NBO(0), EBO(0), CBO(0), indicesCount(0) {}

CurveRenderer::~CurveRenderer() { release(); }

void CurveRenderer::createVBO(Spline *spline, bool use_curvature_color, float radius) {
  release();
  const int segments = 16;
  std::vector<Eigen::Vector3f> _points, _tangents, _normals;
  std::vector<float> _curvatures;
  CurveProcessor::samplePoints(spline, 0.01f, _points, _tangents, _normals, _curvatures);

  // Must have 2 point or more
  if (_points.size() < 2) {
    return;
  }

  std::vector<float> vertices;
  vertices.reserve(_points.size() * 3);
  std::vector<float> normals;
  normals.reserve(_points.size() * 3);
  std::vector<float> colors;
  colors.reserve(_points.size() * 3);
  std::vector<unsigned int> indices;
  for (int i = 0; i < _points.size(); i++) {
    Eigen::Vector3f &tangent = _tangents[i];
    //
    Eigen::Vector3f a = _normals[i];
    Eigen::Vector3f b = _tangents[i].cross(_normals[i]);

    float value = 0.0f;
    if (use_curvature_color) {
        value = std::clamp(_curvatures[i], 0.0f, 10.0f) / 10.0f;
    }
    tinycolormap::Color color = tinycolormap::GetHeatColor(value);

    // Make the points
    for (int j = 0; j < segments; j++) {
      float theta = 2.0f * M_PI * float(j) / float(segments);

      Eigen::Vector3f pt = cos(theta) * a * radius + sin(theta) * b * radius;
      vertices.push_back(_points[i].x() + pt.x());
      vertices.push_back(_points[i].y() + pt.y());
      vertices.push_back(_points[i].z() + pt.z());

      pt = pt.normalized();
      normals.push_back(pt[0]);
      normals.push_back(pt[1]);
      normals.push_back(pt[2]);

      colors.push_back(color.r());
      colors.push_back(color.g());
      colors.push_back(color.b());
    }
  }
  // Setup the indices
  for (int i = 1; i < _points.size(); i++) {
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

  if (spline->getLoop()) {

    int offset = 0;

    float dot = _normals[0].dot(_normals[_normals.size() - 1]);
    dot = std::clamp(dot, -1.0f, 1.0f);

    float angle = std::acos(dot);

    offset = segments - static_cast<int>((angle / (2.0f * M_PI)) * segments) % segments;

    for (int j = 0; j < segments; j++) {
      int i = _points.size() - 1;
      int p0 = i * segments + (j - 1 + segments) % segments;
      int p1 = i * segments + j;
      int p2 = (j - 1 + segments + offset) % segments;
      int p3 = (j + offset) % segments;

      indices.push_back(p1);
      indices.push_back(p0);
      indices.push_back(p2);

      indices.push_back(p1);
      indices.push_back(p2);
      indices.push_back(p3);
    }
  }

  // Setup VAO, VBO, NBO, EBO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &NBO);
  glGenBuffers(1, &CBO);
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

  glBindBuffer(GL_ARRAY_BUFFER, CBO);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),
               GL_STATIC_DRAW);

  glBindVertexArray(0);

  indicesCount = indices.size();
}

void CurveRenderer::draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

void CurveRenderer::setColor(Spline* spline, bool use_curvature_color)
{
    const int segments = 16;
    std::vector<float> _curvatures;
    CurveProcessor::sampleCurvature(spline, 0.01f, _curvatures);

    // Must have 2 point or more
    if (_curvatures.size() < 2) {
        return;
    }

    std::vector<float> colors;
    colors.reserve(_curvatures.size() * 3);
    for (int i = 0; i < _curvatures.size(); i++) {
        float value = 0.0f;
        if (use_curvature_color) {
            value = std::clamp(_curvatures[i], 0.0f, 10.0f) / 10.0f;
        }
        tinycolormap::Color color = tinycolormap::GetHeatColor(value);
        // Make the points
        for (int j = 0; j < segments; j++) {
            colors.push_back(color.r());
            colors.push_back(color.g());
            colors.push_back(color.b());
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, colors.size() * sizeof(float), colors.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CurveRenderer::release() {
  indicesCount = 0;
  if (VAO)
    glDeleteVertexArrays(1, &VAO);
  if (VBO)
    glDeleteBuffers(1, &VBO);
  if (NBO)
    glDeleteBuffers(1, &NBO);
  if (CBO)
    glDeleteBuffers(1, &CBO);
  if (EBO)
    glDeleteBuffers(1, &EBO);
}
