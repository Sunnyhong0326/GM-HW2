#pragma once

#include "helpers/arrowhelper.h"
#include "helpers/axeshelper.h"
#include "helpers/boxhelper.h"
#include "helpers/vertexhelper.h"

#include "scene.h"

class Renderer {
public:
  Renderer(int width, int height, Scene *scenePtr);
  ~Renderer();

  void resize(int width, int height);
  void render();

private:
  void setupShaders();
  void releaseShaders();

private:
  int screenWidth;
  int screenHeight;

  // State
  Scene *scene;

  // Shader
  Shader *plyShader;
  Shader *axesShader;
  Shader *colorShader;

  // Helpers
  std::unique_ptr<VertexHelper> vertexHelper;
  std::unique_ptr<AxesHelper> axesHelper;
  std::unique_ptr<BoxHelper> boxHelper;
  std::unique_ptr<ArrowHelper> arrowHelper;
};
