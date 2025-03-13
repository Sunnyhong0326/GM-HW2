#pragma once

#include "Spline.h"

class Polyline : public Spline
{
protected:
  void build() override;
public:
  Polyline() : Spline(Type::Polyline) {}
};

