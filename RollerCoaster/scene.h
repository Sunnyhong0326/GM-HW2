#pragma once

#include "miscellaneous/camera.h"
#include "model.h"
#include <memory>
#include <vector>

class Scene {
public:
  // Constructor
  Scene(std::unique_ptr<Model> model, int width, int height);

  // Resize
  void resize(int width, int height);

  // Getters
  inline Camera *getCamera() const { return camera.get(); }
  inline Model *getModel() const { return model.get(); }
  inline float getTimeElapsed() const { return timeElapsed; }
  void setTimeElapsed(float t)  { timeElapsed = t; }

  // Setters
  void update();
  void updateCarts();
  void updateCurveRenderer();

  bool getShowPoints() { return showPoints; }
  void setShowPoints(bool flag) { showPoints = flag; }
  bool getShowFarmes() { return showFrames; }
  void setShowFarmes(bool flag) { showFrames = flag; }
  bool getShowCurvatures() { return showCurvatures; }
  void setShowCurvatures(bool flag);
  void toggleAnimation();
  bool getAnimation() { return isAnimating; }

private:

  std::unique_ptr<Model> model;
  std::unique_ptr<Camera> camera;

  int screenWidth;
  int screenHeight;

  // Vis Flags
  bool showPoints;
  bool showFrames;
  bool showCurvatures;
  bool isAnimating;
  float lastFrameTime;
  float timeElapsed;

  void resetVis();
  void setupCamera();

};
