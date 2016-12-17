#pragma once

#include <memory>
#include <cmath>
#include "../World.hpp"
#include "Bullet.hpp"
#include "../consts.hpp"


	// PATRZ DO costs.hpp
struct Basic : public GameObject {
  float size = Basic_size;
  float range = Basic_range;  
  float speed = Basic_speed;
  float vx, vy;
  float attackTimer = AttackTimer; 
  float timeSinceLastAttack = TimeSinceLastAttack;

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
      world.spawn(std::make_shared<Bullet>(team, 100.0f, x, y, opponent->x,
                                           opponent->y));
    }
    // remove from board
  };
  virtual void move(float dt) {
    x += vx * dt;
    y += vy * dt;

    if (x < size) {
      x = size;
      vx = -vx;
    } else if (x > screenWidth - size) {
      x = screenWidth - size;
      vx = -vx;
    }

    if (y < size) {
      y = size;
      vy = -vy;
    } else if (y > screenHeigth - size) {
      y = screenHeigth - size;
      vy = -vy;
    }
  };
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
