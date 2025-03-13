#include "scene.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <glad/glad.h>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>

// Constants
#define M_PI 3.14159265358979323846f
static constexpr float deg2rad(float degrees) { return degrees * (M_PI / 180.0f); }


Scene::Scene(std::unique_ptr<Model> model, int width, int height)
    : model(std::move(model)), screenWidth(width), screenHeight(height), 
      timeElapsed(0), isAnimating(false), showPoints(true), showFrames(false), showCurvatures(false){
  setupCamera();
  resetVis();
  
  lastFrameTime = static_cast<float>(glfwGetTime());
}

void Scene::update() {
  float currentTime = static_cast<float>(glfwGetTime());
  float deltaTime = currentTime - lastFrameTime;
  lastFrameTime = currentTime;

  if (isAnimating) {
    timeElapsed += deltaTime;
    updateCarts();
  }
}

void Scene::updateCarts()
{
    std::vector<Cart>& carts = model->getCarts();
    for (int i = 0; i < (int)carts.size(); i++)
    {
        carts[i].update(model->getSpline(), timeElapsed,
            model->getUseUntiSpeed(),
            model->getUseBishop());
    }
}

void Scene::updateCurveRenderer()
{
    model->getCurveRenderer()->createVBO(model->getSpline(), showCurvatures);
}

void Scene::setupCamera() {
  camera = std::make_unique<Camera>();
  camera->setViewport(screenWidth, screenHeight);
  camera->setPosition(Eigen::Vector3f(0, 0, 5.0f));
  camera->setTarget(Eigen::Vector3f(0, 0, 0));
  camera->setFovY(deg2rad(45.0f));
}

void Scene::resetVis() { 
    isAnimating = false; 
    showPoints = true;
    showFrames = false;
    showCurvatures = false;
}

void Scene::resize(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  camera->setViewport(width, height);
}

void Scene::setShowCurvatures(bool flag)
{
    showCurvatures = flag;
    model->getCurveRenderer()->setColor(model->getSpline(), showCurvatures);
}

void Scene::toggleAnimation() {
  isAnimating = !isAnimating;
}
