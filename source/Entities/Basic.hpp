#pragma once

#include <memory>
#include <cmath>
#include "../World.hpp"
#include "Bullet.hpp"

struct Basic : public GameObject {
  float size = 10.0;
  float range = 70;  // TEMPORARY
  float speed;
  float vx, vy;
  float attackTimer = 1.0;  // TEMPORARY
  float timeSinceLastAttack = 0.0;

  Basic(unsigned team) : GameObject{"Basic", team, 0, 0, 10} {
    speed = 250;
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
    } else if (x > 1920 - size) {
      x = 1920 - size;
      vx = -vx;
    }

    if (y < size) {
      y = size;
      vy = -vy;
    } else if (y > 1080 - size) {
      y = 1080 - size;
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
    object->Set(v8::String::NewFromUtf8(isolate, "_hp_"),
                v8::Number::New(isolate, hp));
  }
};
