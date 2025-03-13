#pragma once

#include "Spline.h"

class CatmullRom : public Spline
{
protected:
  void build() override;
public:
  CatmullRom() : Spline(Type::CatmullRom) {}
};

