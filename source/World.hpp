#pragma once
#include "GameObject.hpp"
#include <memory>

class Basic;

struct World {
  float worldSizeX = 500.0;
  float worldSizeY = 500.0;
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
  void remove(std::shared_ptr<GameObject> go) {
    objects[go->id] = nullptr;  // Terrible hack
  }
  void step() {
    if (!toBeAdded.empty()) {
      objects.insert(objects.end(), toBeAdded.begin(), toBeAdded.end());
      toBeAdded.clear();
    }
    float dt = 1.0f / 60;
    for (auto& go : objects) {
      if (objects[go->id] != nullptr)  // Terrible hack
        go->update(dt);
    }
  }

  std::vector<std::shared_ptr<GameObject> > getObjectsInRadius(float x,
                                                               float y,
                                                               float radius);

  std::shared_ptr<Basic> getNearestUnit(float x, float y, float radius);
};
