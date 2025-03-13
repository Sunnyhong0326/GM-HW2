#pragma once

#include <Eigen/Dense>
#include <vector>
#include "Spline.h"

class Cart
{
private:
	float m_Offset;
	Eigen::Vector3f m_Posn;
	Eigen::Vector3f m_Tangent;
	Eigen::Vector3f m_Normal;

public:

	Cart();
	Cart(float offset);
	~Cart();

	void update(Spline* spline, float t, bool useUnitSpeed, bool useBishop);

	Eigen::Vector3f& resetNormal();
	const Eigen::Vector3f& getPosition() const { return m_Posn; }
	const Eigen::Vector3f& getTangent() const { return m_Tangent; }
	const Eigen::Vector3f& getNormal() const { return m_Normal; }
};

