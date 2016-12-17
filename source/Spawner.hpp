#pragma once
#include "Entities/Basic.hpp"
#include "Entities/Tank.hpp"
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
    std::shared_ptr<GameObject> ball;

    if (randRange(0, 10) >= 5) {
      ball = std::make_shared<Tank>(team);
    } else {
      ball = std::make_shared<Basic>(team);
    }

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
