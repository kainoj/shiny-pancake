#pragma once

#include <memory>
#include <cmath>
#include "../World.hpp"
#include "Bullet.hpp"
#include "../consts.hpp"

enum class State{
  Attack,
  Engaging,
  Seeking,
};

// PATRZ DO costs.hpp
struct Basic : public GameObject {
  float size = BasicSize;
  float range = BasicRange;
  float speed = BasicSpeed;
  float vx, vy;
  float attackTimer = BasicAttackTimer;
  float timeSinceLastAttack = BasicTimeSinceLastAttack;
  float communicationRange = CommunicationRange;
  std::shared_ptr<Basic> opponent;
  State state = State::Seeking;

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
      World &world = World::getInstance();
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
    World &world = World::getInstance();
    auto enemy = world.getNearestUnit(x, y, range, team);
    if(enemy != nullptr)
    {
      opponent = enemy;
      state = State::Attack;
    }
    if(state == State::Seeking)
    {  
      auto objects = world.getAlliedObjectsInRadius(x, y, communicationRange, team);
      for(auto& go : objects){
        if(go->state == State::Attack || go->state == State::Engaging)
        {
          opponent = go->opponent;
          state = State::Engaging;
          break;
        }
      }
      if(opponent == nullptr && distance(vx, vy, 0, 0) < speed)
      {
        calculateSpeedVector();
      }
      move(dt);
    
    }
    if(state == State::Engaging)
    {
      if(opponent == nullptr || opponent->hp <= 0)
      {
        opponent = nullptr;
        state = State::Seeking;
      }
      else{
        if(distance(x, y, opponent->x, opponent->y) <= range)
        {
          state = State::Attack;
        }
        else
        {
          vx = opponent->x - x;
          vy = opponent->y - y;
          move(dt);
        }
      }
    }
    if(state == State::Attack)
    {
      if(opponent == nullptr || opponent->hp <= 0)
      {
        opponent = nullptr;
        state = State::Seeking;
      }
      else{
        if(distance(x, y, opponent->x, opponent->y) > range)
        {
          state = State::Engaging;
        }
        else
          attack(opponent, 10, dt);
      }
    }
  };

  virtual void updateHP(float dmg) { // dammage taken
    hp -= dmg;
  }

  virtual void getValue(v8::Isolate *isolate, v8::Local<v8::Object> object) {
    GameObject::getValue(isolate, object);
  }
};
