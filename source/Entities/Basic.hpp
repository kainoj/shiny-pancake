#pragma once

#include <memory>
#include <cmath>
#include "../World.hpp"
#include "Bullet.hpp"
#include "../consts.hpp"

// PATRZ DO costs.hpp
struct Basic : public GameObject {
  float size = BasicSize;
  float range = BasicRange;
  float speed = BasicSpeed;
  float vx, vy;
  float attackTimer = BasicAttackTimer;
  float timeSinceLastAttack = BasicTimeSinceLastAttack;

  Basic(unsigned team) : GameObject{"Basic", team, 0, 0, 10} {
    calculateSpeedVector();
  }

  void calculateSpeedVector() {
    vx = randRange(3, 7) * (speed / 10.0) * (randRange(0, 1) ? 1 : -1);
    vy = sqrtf(speed * speed - (vx * vx)) * (randRange(0, 1) ? 1 : -1);
  }

  virtual void attack(std::shared_ptr<Basic> opponent, float dmg, float dt) {
    timeSinceLastAttack += dt;
    if (timeSinceLastAttack > attackTimer) {
      timeSinceLastAttack = timeSinceLastAttack - attackTimer;
      World& world = World::getInstance();
      world.spawn(std::make_shared<Bullet>(team, 200.0f, x, y, opponent->x,
                                           opponent->y));
    }
  };

  virtual void move(float dt) {
    x += vx * dt;
    y += vy * dt;

    if (x < size) {
      x = size;
      vx = -vx;
    } else if (x > ScreenWidth - size) {
      x = ScreenWidth - size;
      vx = -vx;
    }

    if (y < 30 + size) {
      y = 30 + size;
      vy = -vy;
    } else if (y > ScreenHeigth - size) {
      y = ScreenHeigth - size;
      vy = -vy;
    }
  };

  virtual unsigned score() { return 1; }

  virtual void update(float dt) {
    std::shared_ptr<Basic> opponent =
        World::getInstance().getNearestUnit(x, y, range, team);
    if (opponent != nullptr) {
      // found an opponent
      attack(opponent, 10, dt);  // RANDOM DMG
    } else {
      // search for an opponent
      move(dt);
    }
  };

  virtual void updateHP(float dmg) {  // dammage taken
    hp -= dmg;
  }

  virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
    GameObject::getValue(isolate, object);
  }
};
