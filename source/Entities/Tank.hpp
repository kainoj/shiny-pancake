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
};
