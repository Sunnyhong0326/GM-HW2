#pragma once
#include "learnply.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class MeshProcessor {
public:
  MeshProcessor() = delete;

  // Calc Functions from learnply
  static void calcVertNormals(Polyhedron *poly);
  static void calcFaceNormalsAndArea(Polyhedron *poly);
  static void calcBoundingSphere(Polyhedron *poly);
  static void calcEdgeLength(Polyhedron *poly);

  // Getters
  static std::vector<Triangle *> &getTriangles(Polyhedron *poly) {
    return poly->tlist;
  }
  static std::vector<Vertex *> &getVertices(Polyhedron *poly) {
    return poly->vlist;
  }
  static std::vector<Edge *> &getEdges(Polyhedron *poly) { return poly->elist; }
  static std::vector<Corner *> &getCorners(Polyhedron *poly) {
    return poly->clist;
  }
};
