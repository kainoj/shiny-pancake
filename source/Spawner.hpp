#pragma once
#include "Entities/Basic.hpp"
#include <memory>

struct Spawner : public GameObject {
  float spawnTimer;
  float timeSinceLastSpawn;
  int spawnCount = 0;
  Spawner(float spawnTimer_)
      : GameObject{"Spawner", randRange(1, 2), 0, 0},
        timeSinceLastSpawn{0.0},
        spawnTimer{spawnTimer_} {}
  virtual std::shared_ptr<GameObject> getObject() {
    auto ball = std::make_shared<Basic>();
    ball->x = x + rand() % 100;
    ball->y = y + rand() % 100;
    return ball;
  }
  virtual void update(float dt) {
    timeSinceLastSpawn += dt;
    if (timeSinceLastSpawn > spawnTimer) {
      timeSinceLastSpawn = timeSinceLastSpawn - spawnTimer;
      spawn();
    }
  };
  virtual void spawn() {
    World& world = World::getInstance();
    world.spawn(getObject());
  }
};
