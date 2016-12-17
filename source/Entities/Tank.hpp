#pragma once

#include "../World.hpp"

struct Tank : public Basic {
  Tank(unsigned team) : Basic(team) {
    type = "Tank";
    range *= 0.5;
    speed *= 0.7;
  }
};
