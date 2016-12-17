#pragma once

#include "../World.hpp"
#include "../consts.hpp"

struct Tank : public Basic {
  Tank(unsigned team) : Basic(team) {
    type = "Tank";
    range *= TankRange;
    speed *= TankSpeed;
    size = TankSize;
    calculateSpeedVector();
  }

  virtual unsigned score() { return 2; }
  virtual void updateHP(float dmg) { hp -= TankDmgReduce * dmg; }
  virtual void update(float dt) {
    Basic::update(dt);
    World& world = World::getInstance();
    for (auto& bullet : world.getBulletsInRadius(x, y, size * 20, team)) {
      bullet->velX += x > bullet->x ? 1 : -1;
      bullet->velY += y > bullet->y ? 1 : -1;
    }
  }
};
