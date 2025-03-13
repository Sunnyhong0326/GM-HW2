#pragma once

#include "Curve.h"
#include <Eigen/Dense>
#include <vector>

class Spline
{
public:
    enum class Type {
        Polyline = 0,
        BSpline = 1,
        CatmullRom = 2,
        Error = 404
    };

protected:
  std::vector<Eigen::Vector3f> m_points;  // Control Points
  std::vector<Curve> m_curves;            // Curves
  float arcLength;
  std::vector<float> preLength;           // Prefix of Curve Length

  bool m_loop;    // Loop Spline
  Type m_type;            // Spline Type
  int selectedIdx = -1;   // Selected Index


protected:
  virtual void build();

public:
  Spline(Type type) : m_loop(false), m_type(type), arcLength(0.0f){}

  // Control Points
  virtual void addPoint();
  virtual void addPoint(Eigen::Vector3f& p);
  virtual void removePoint();
  virtual void addCurve(
      const Eigen::Vector3f& a,
      const Eigen::Vector3f& b,
      const Eigen::Vector3f& c,
      const Eigen::Vector3f& d,
      Eigen::Matrix4f& M
  );

  // Get Position in specific Time
  Eigen::Vector3f getPosition(float t, bool flagUS);
  Eigen::Vector3f getTangent(float t, bool flagUS);
  double getCurvature(float t, bool flagUS);
  //
  std::pair<int, float> parameterize(float t);
  Eigen::Vector3f getPositionU(float u);
  Eigen::Vector3f getTangentU(float u);
  double getCurvatureU(float u);
  // UnitSpeed
  std::pair<int, float> parameterizeUnitSpeed(float s);
  Eigen::Vector3f getPositionS(float s);
  Eigen::Vector3f getTangentS(float s);
  double getCurvatureS(float s);

  // Other Getter
  inline int getNumCurves() { return (int)m_curves.size(); }
  inline std::vector<Curve>& getCurves() { return m_curves; }
  inline std::vector<Eigen::Vector3f>& getPoints() { return m_points; }
  inline Type getType() { return m_type; }
  inline bool getLoop() const { return m_loop; }

  // Selection
  const int getSelectedIdx() const { return selectedIdx; };
  Eigen::Vector3f getSelectedPoint() const;
  bool isSelectedPoint() const;

  // Setter
  void setSelectedIdx(int idx) { selectedIdx = idx; }
  void setLoop(bool loop);
  void setPoints(std::vector<Eigen::Vector3f>& points);
  void setAntribute(std::vector<Eigen::Vector3f>& points, bool loop);
  void setSelectedPoint(Eigen::Vector3f& p);
};