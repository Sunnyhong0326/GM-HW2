#pragma once
#include <memory>
#include "mesh/learnply.h"
#include "mesh/meshrenderer.h"
#include "curves/Spline.h"
#include "curves/CurveRenderer.h"
#include "curves/Cart.h"

class Model {
public:
  Model();

  // Setters for internal objects
  void setPolyhedron(Polyhedron *polyhedron);
  void setSpline(Spline* curve);

  // Getters for internal objects
  Polyhedron *getPolyhedron() { return polyhedron.get(); }
  MeshRenderer *getMeshRenderer() { return meshRenderer.get(); }
  Spline* getSpline() const { return spline.get(); }
  CurveRenderer* getCurveRenderer() { return curveRenderer.get(); }
  bool getUseUntiSpeed() const { return useUntiSpeed; }
  void setUseUntiSpeed(bool flag) { useUntiSpeed = flag; }
  bool getUseBishop() const { return useBishop; }
  void setUseBishop(bool flag) { useBishop = flag; }
  std::vector<Cart>& getCarts() { return carts; }

private:
  std::unique_ptr<Polyhedron> polyhedron;
  std::unique_ptr<MeshRenderer> meshRenderer;
  std::unique_ptr<Spline> spline;
  std::unique_ptr<CurveRenderer> curveRenderer;
  std::vector<Cart> carts;

  bool useUntiSpeed;
  bool useBishop;
};
