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
    Eigen::Matrix4f matM, matMFL;
    matM << -0.5f, 1.5f, -1.5f, 0.5f,
        1.0f, -2.5f, 2.0f, -0.5f,
        -0.5f, 0.0f, 0.5f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f;

    matMFL << 2.0f, -2.0f, 1.0f, 1.0f,
        -3.0f, 3.0f, -2.0f, -1.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f;
    int n = static_cast<int>(m_points.size());

    if (m_loop) {
        // Closed Catmull-Rom Spline (Looping)
        for (int i = 0; i < n; i++) {
            addCurve(
                m_points[(i - 1 + n) % n],  // P0
                m_points[i % n],            // P1
                m_points[(i + 1) % n],      // P2
                m_points[(i + 2) % n],      // P3
                matM);
        }
    }
    else if (n > 3) {
        // Open Catmull-Rom Spline

        // First segment (H-spline)
        addCurve(
            m_points[0],
            m_points[1],
            m_points[1] - m_points[0],   // t0
            (m_points[0] + m_points[2]) / 2,  // t1
            matMFL
        );

        // Middle segments (Standard Catmull-Rom)
        for (int i = 1; i < n - 3; i++) {
            addCurve(
                m_points[i],
                m_points[i + 1],
                m_points[i + 2],
                m_points[i + 3],
                matM
            );
        }

        // Last segment (H-spline)

        //addCurve(
        //    m_points[n - 2],
        //    m_points[n - 1],
        //    (m_points[n - 2] + m_points[n]) / 2,  // tn-1
        //    Eigen::Vector3f::Zero(),   // tn
        //    matMFL
        //);
    }

}