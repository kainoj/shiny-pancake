#pragma once

#include "../World.hpp"
#include "../consts.hpp"

struct Tank : public Basic {
  Tank(unsigned team) : Basic(team) {
    type = "Tank";
    range *= Tank_range;
    speed *= Tank_speed;
    calculateSpeedVector();
  }

  virtual void updateHP(float dmg) { hp -= Tank_dmg_reduce * dmg; }
};
