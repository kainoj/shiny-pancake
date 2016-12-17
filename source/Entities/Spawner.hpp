#pragma once
#include "Basic.hpp"
#include "Sniper.hpp"
#include "Tank.hpp"
#include <memory>

#include <map>

struct Cooldowns {
  int cdSniper;
  int cdTank;

  std::map<char, int> cd;

  Cooldowns() {
    cdSniper = 15;
    cdTank = 7;
    cd['S'] = 6;
    cd['T'] = 3;
  }
};

struct Spawner : public Basic {
  float spawnTimer;
  float timeSinceLastSpawn;
  int spawnCount = 0;
  Cooldowns cooldowns;
  Spawner(float spawnTimer_, unsigned team)
      : Basic{team}, spawnTimer{spawnTimer_}, timeSinceLastSpawn{0.0} {
    type = "Spawner";
  }
  virtual std::shared_ptr<GameObject> getObject() {
    std::shared_ptr<GameObject> ball;

    if (cooldowns.cd['S'] <= 0) { // spawn Sniper
      ball = std::make_shared<Sniper>(team);
      cooldowns.cd['S'] = cooldowns.cdSniper;
    } else if (cooldowns.cd['T'] <= 0) { // spawn Tank
      ball = std::make_shared<Tank>(team);
      cooldowns.cd['T'] = cooldowns.cdTank;
    } else { // spawn Basic
      ball = std::make_shared<Basic>(team);
      cooldowns.cd['S'] -= 1;
      cooldowns.cd['T'] -= 1;
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
    World &world = World::getInstance();
    world.spawn(getObject());
  }
};
