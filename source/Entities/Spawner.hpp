#pragma once
#include "Basic.hpp"
#include "Sniper.hpp"
#include "Tank.hpp"
#include <memory>

struct Spawner : public Basic {
  float spawnTimer;
  float timeSinceLastSpawn;
  int spawnCount = 0;
  Spawner(float spawnTimer_, unsigned team)
      : Basic{team}, spawnTimer{spawnTimer_}, timeSinceLastSpawn{0.0} {
    type = "Spawner";
  }
  virtual std::shared_ptr<GameObject> getObject() {
    std::shared_ptr<GameObject> ball;

    unsigned choice = randRange(0, 10);

    if (choice >= 9) {
      ball = std::make_shared<Sniper>(team);
    } else if (choice >= 6) {
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
