#include "CatmullRom.h"
#include <algorithm>
#include <cmath>

void CatmullRom::build() {
    Spline::build();
    if (m_points.size() < 4) return;
    /*
      TODO: Implement the function to build the Catmull-Rom spline.
      Hint:
      1. Use addCurve to create the segments of the B-spline
      2. If m_loop is true, create the close Catmull-Rom spline with m_points
      3. Otherwise, create the open Catmull-Rom spline with m_points
         Note, the open Catmull-Rom spline goes through p0 and pn
    */
}