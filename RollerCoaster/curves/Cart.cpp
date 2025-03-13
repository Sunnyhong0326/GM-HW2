#include "Cart.h"
#include "CurveProcessor.h"

Cart::Cart()
    : m_Offset(0.0f), m_Posn(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
      m_Tangent(Eigen::Vector3f(1.0f, 0.0f, 0.0f)), m_Normal(Eigen::Vector3f(0.0f, 0.0f, 0.0f)) {}

Cart::Cart(float offset)
    : m_Offset(offset), m_Posn(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
      m_Tangent(Eigen::Vector3f(1.0f, 0.0f, 0.0f)), m_Normal(Eigen::Vector3f(0.0f, 1.0f, 0.0f)) {}

Cart::~Cart() {}

void Cart::update(Spline *spline, float t, bool useUnitSpeed, bool useBishop) {
  float u = t - m_Offset;
  if (u < 0.0f) {
    u = 0.0f;
  }
  Eigen::Vector3f t0 = m_Tangent;
  Eigen::Vector3f n0 = m_Normal;
  m_Posn = spline->getPosition(u, useUnitSpeed);
  m_Tangent = spline->getTangent(u, useUnitSpeed);
  m_Tangent.normalize();
  if (useBishop && m_Normal.squaredNorm() > 0.1f) {
    m_Normal = CurveProcessor::parallelTransport(n0, t0, m_Tangent);
    m_Normal.normalize();
  } else {
    Eigen::Vector3f up = Eigen::Vector3f(0.0f, 1.0f, 0.0f);
    if (m_Tangent.dot(up) > 0.99f)
      up = Eigen::Vector3f(1, 0, 0);
    m_Normal = m_Tangent.cross(up).normalized();
  }
}

Eigen::Vector3f &Cart::resetNormal() {
  m_Normal << 0.0f, 0.0f, 0.0f;
  return m_Normal;
}
