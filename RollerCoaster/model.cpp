#include "model.h"
#include "curves/Polyline.h"

Model::Model():
	meshRenderer(std::make_unique<MeshRenderer>()),
	curveRenderer(std::make_unique<CurveRenderer>()),
	spline(std::make_unique<Polyline>()),
	useUntiSpeed(false), useBishop(false)
{ 
	carts.emplace_back(0.0f);
	carts.emplace_back(0.15f);
	carts.emplace_back(0.30f);
};

void Model::setPolyhedron(Polyhedron *poly) {
  polyhedron.reset(poly);
  polyhedron->initialize();

  MeshProcessor::calcEdgeLength(polyhedron.get());
  MeshProcessor::calcBoundingSphere(polyhedron.get());
  MeshProcessor::calcFaceNormalsAndArea(polyhedron.get());
  MeshProcessor::calcVertNormals(polyhedron.get());

  meshRenderer->setupBuffers(poly);
  meshRenderer->setNormalMode(poly, false);
  meshRenderer->setColors(poly, 0);
}

void Model::setSpline(Spline* curve)
{
	spline.reset(curve);
}