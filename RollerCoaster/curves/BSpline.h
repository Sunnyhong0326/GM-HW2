#pragma once

#include "Spline.h"

class BSpline : public Spline
{
protected:
  void build() override;
public:
  BSpline() : Spline(Type::BSpline) {}
};

