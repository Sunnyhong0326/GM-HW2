#pragma once
#include <string>
#include <vector>

#include "../Model.h"
#include "Spline.h"

class CurveProcessor {
public:
  CurveProcessor() = delete;

  static void samplePoints(Spline *spline, float segLen, std::vector<Eigen::Vector3f> &pos,
                           std::vector<Eigen::Vector3f> &tangent,
                           std::vector<Eigen::Vector3f> &normal, 
                           std::vector<float> &curvature);
  static void sampleCurvature(Spline *spline, float segLen, std::vector<float> &curvature);

  static Eigen::Vector3f parallelTransport(Eigen::Vector3f &u0, Eigen::Vector3f &t0,
                                           Eigen::Vector3f &t1);

  // Save or Load Spline
  static void saveSpline(Spline *spline);
  static bool loadSpline(Model *model);

  static bool convertSplineType(Model *model, Spline::Type type);
};
