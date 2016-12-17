#pragma once
#include "GameObject.hpp"
#include <memory>
#include <list>
#include <queue>
#include <algorithm>

class Basic;

struct World {
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
    float dt = 1.0f / 60;
    time += dt;
    for (auto& go : objects) {
        go->update(dt);
    }
  }

 	void removeObjects()
 	{
 		for (auto it = objects.begin(); it != objects.end(); it++)
 		{
 			auto go = *it;
 			while(go->hp <= 0)
 			{
 				it = objects.erase(it);
 				go = *it;
 			}
 		}
 	}

  std::vector<std::shared_ptr<GameObject> > getObjectsInRadius(float x,
                                                               float y,
                                                               float radius);

  std::shared_ptr<Basic> getNearestUnit(float x, float y, float radius,
                                        unsigned team);

  std::shared_ptr<Basic> collidesWithUnit(float x, float y, unsigned);
};
