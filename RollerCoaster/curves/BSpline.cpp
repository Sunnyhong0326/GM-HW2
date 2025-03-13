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
}