#pragma once

#include "../World.hpp"
#include "../consts.hpp"

struct Sniper : public Basic {
  Sniper(unsigned team) : Basic(team) {
    type = "Sniper";
    size = SniperSize;
    range = SniperRange;
    attackTimer = SniperAttackTimer;
  }

  virtual unsigned score() { return 3; }
};
