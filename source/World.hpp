#pragma once
#include "GameObject.hpp"
#include <memory>
#include <list>
#include <queue>
#include <algorithm>
#include <chrono>

class Basic;

struct World {
  std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
  float worldSizeX = 1920.0;
  float worldSizeY = 1080.0;
  float time = 0.0;
  static World& getInstance() {
    static World goFactory;
    return goFactory;
  }
  std::queue<unsigned> freeIds;
  std::vector<std::shared_ptr<GameObject> > toBeAdded;
  std::vector<std::shared_ptr<GameObject> > objects;
  int currentObjectID = 0;
  void spawn(std::shared_ptr<GameObject> go) {
    go->id = ++currentObjectID;
    toBeAdded.push_back(go);
  }
  void step() {
    if (!toBeAdded.empty()) {
      objects.insert(objects.end(), toBeAdded.begin(), toBeAdded.end());
      toBeAdded.clear();
    }

    std::chrono::duration<float> elapsed_seconds = std::chrono::steady_clock::now()-start;
    float dt = elapsed_seconds.count();
    time += dt;
    start=std::chrono::steady_clock::now();
    for (auto& go : objects) {
      go->update(dt);
    }
  }

  void removeObjects() {
    for (auto it = objects.begin(); it != objects.end();) {
      auto go = *it;
      if (go->hp <= 0) {
        it = objects.erase(it);
      } else {
        it++;
      }
    }
  }

  std::vector<std::shared_ptr<GameObject> > getObjectsInRadius(float x,
                                                               float y,
                                                               float radius);

  std::shared_ptr<Basic> getNearestUnit(float x,
                                        float y,
                                        float radius,
                                        unsigned team);

  std::shared_ptr<Basic> collidesWithUnit(float x, float y, unsigned);
};
