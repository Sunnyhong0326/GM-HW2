#include "BSpline.h"
#include <algorithm>
#include <cmath>

void BSpline::build() {
  Spline::build();
  if (m_points.size() < 4) return;
  /*
  TODO: Implement the function to build the B-spline.
  Hint:
  1. Use addCurve to create the segments of the B-spline
  2. If m_loop is true, create the close B-spline with m_points
  3. Otherwise, create the open uniform B-spline with m_points
     Note, the open uniform B-spline goes through p0 and pn
  */
  Eigen::Matrix4f matM;
  matM << -1.0f, 3.0f, -3.0f, 1.0f,
      3.0f, -6.0f, 3.0f, 0.0f,
      -3.0f, 0.0f, 3.0f, 0.0f,
      1.0f, 4.0f, 1.0f, 0.0f;
  matM = matM / 6;

  int n = static_cast<int>(m_points.size());

  if (m_loop) {
      for (int i = 0; i < n; i++) {
          addCurve(
              m_points[(i - 1 + n) % n],  // P0
              m_points[i % n],            // P1
              m_points[(i + 1) % n],      // P2
              m_points[(i + 2) % n],      // P3
              matM);
      }
  }
  else {
      for (int i = 0; i < n-3; i++) {
          addCurve(
              m_points[i],          // P0
              m_points[i + 1],      // P1
              m_points[i + 2],      // P2
              m_points[i + 3],      // P3
              matM);
      }
  }
}