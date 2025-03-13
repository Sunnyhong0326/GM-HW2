#pragma once

#include "../miscellaneous/tinycolormap.hpp"
#include "Spline.h"
#include <algorithm>
#include <glad/glad.h>
#include <vector>

// Cylinder here only help to generate cylinder vertices or Pipe
class CurveRenderer {
public:
  CurveRenderer();
  ~CurveRenderer();

  // Init Pipe, Only Create pipe if the points is continuous
  void createVBO(Spline *spline, bool use_curvature_color, float radius = 0.02f);
  // Draw
  void draw();
  void setColor(Spline* spline, bool use_curvature_color);

private:
  GLuint VAO, VBO, NBO, EBO, CBO;
  size_t indicesCount;

  void release();
};
