#include "Curve.h"
#include <iostream>
#include <Eigen/Dense>

// Pre Calculate M * P for the formula of C(u) = T * M * P
Curve::Curve(const Eigen::Vector3f& a, const Eigen::Vector3f& b,
      const Eigen::Vector3f& c, const Eigen::Vector3f& d,
      Eigen::Matrix4f& M) : length(0) {
  Eigen::Matrix<float, 4, 3> P;
  P <<
    a.transpose(),
    b.transpose(),
    c.transpose(),
    d.transpose();
  mMP = M * P;
}

// Calculate C(u) = T * M * P
Eigen::Vector3f Curve::getPosition(float u) {
  Eigen::Matrix<float, 1, 4> matU;
  matU << u * u * u, u * u, u, 1.0f;
  Eigen::Vector3f ret = (matU * mMP).transpose();
  return ret;
}

// Calculate the unit tangent vector at u
Eigen::Vector3f Curve::getTangent(float u) {
  Eigen::Matrix<float, 1, 4> matU;
  matU << 3.0f * u * u, 2.0f * u, 1.0f, 0.0f;
  Eigen::Vector3f ret = (matU * mMP).transpose();
  return ret;
}

/*
  TODO: Implement the function to compute the curvature.
*/
float Curve::getCurvature(float u)
{
    // Compute first derivative (tangent)
    Eigen::Vector3f alpha_prime = getTangent(u);

    // Compute second derivative using central difference
    float h = 1e-4f;  // Small step for finite differences
    Eigen::Vector3f alpha_prime1 = getTangent(u + h);
    Eigen::Vector3f alpha_prime2 = getTangent(u - h);
    Eigen::Vector3f alpha_double_prime = (alpha_prime1 - alpha_prime2) / (2 * h);

    // Compute cross product || £\'(u) ¡Ñ £\''(u) ||
    Eigen::Vector3f cross_product = alpha_prime.cross(alpha_double_prime);
    float numerator = cross_product.norm();

    // Compute || £\'(u) ||^3
    float denominator = std::pow(alpha_prime.norm(), 3);

    // Avoid division by zero
    if (denominator < 1e-6f) return 0.0f;

    return numerator / denominator;
}

// Calculate arc-length
void Curve::calculateFeatures(int segments) {
  length = 0.0f;
  Eigen::Vector3f p0 = getPosition(0.0f);
  for (int i = 1; i < segments; i++) {
    float u = (float)i / (float)segments;
    Eigen::Vector3f p1 = getPosition(u);
    length += (p1 - p0).norm();
    p0 = p1;
  }
}

// Aquire points per length
void Curve::getPoints(float segLen, std::vector<Eigen::Vector3f>& points)
{
    int numSeg = (int)(length / segLen);
    for (int i = 0; i < numSeg; i++) {
        float u = (float)i / (float)numSeg;
        points.push_back(getPosition(u));
    }
}

// Aquire tangent per length
void Curve::getTangents(float segLen, std::vector<Eigen::Vector3f>& tangents)
{
    int numSeg = (int)(length / segLen);
    for (int i = 0; i < numSeg; i++) {
        float u = (float)i / (float)numSeg;
        tangents.push_back(getTangent(u));
    }
}

// Aquire curvatures per length
void Curve::getCurvatures(float segLen, std::vector<float>& curvatures)
{
    int numSeg = (int)(length / segLen);
    for (int i = 0; i < numSeg; i++) {
        float u = (float)i / (float)numSeg;
        curvatures.push_back(getCurvature(u));
    }
}