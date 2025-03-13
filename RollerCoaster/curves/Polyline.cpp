#include "Polyline.h"

void Polyline::build() 
{
  Spline::build();
  if (m_points.size() == 0) return;

  Eigen::Matrix4f matM;
  matM << 0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f,
         -1.0f, 1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f, 0.0f;

  int n = (int)m_points.size();
  int j = m_loop ? n : n - 1;
  for (int i = 0; i < j; i++) {
      addCurve(
      m_points[i % n],
      m_points[(i + 1) % n],
      Eigen::Vector3f::Zero(),
      Eigen::Vector3f::Zero(),
      matM);
  }
}