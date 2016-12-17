#pragma once
#include "Entities/Basic.hpp"
#include <memory>

struct Spawner : public GameObject {
  float spawnTimer;
  float timeSinceLastSpawn;
  int spawnCount = 0;
  Spawner(float spawnTimer_, unsigned team)
      : GameObject{"Spawner", team, 0, 0, 25},
        spawnTimer{spawnTimer_},
        timeSinceLastSpawn{0.0} {}
  virtual std::shared_ptr<GameObject> getObject() {
    auto ball = std::make_shared<Basic>(team);
    ball->x = x + rand() % 10;
    ball->y = y + rand() % 10;
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
