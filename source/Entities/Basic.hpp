#pragma once

#include <cmath>

const float vectorLength = 100.0;

struct Basic : public GameObject {
  float hp = 100;
  float vx = randRange(5,10) * (vectorLength/10.0) * (randRange(0, 1) ? 1 : -1);
  float vy = sqrtf(vectorLength*vectorLength - (vx*vx)) * (randRange(0, 1) ? 1 : -1);
  //float vy = randRange(5,10) * 20 * (randRange(0, 1) ? 1 : -1);
  Basic(unsigned team) : GameObject{"Basic", team, 0, 0, 10} {}
  virtual void update(float dt) {
    x += vx * dt;
    y += vy * dt;

    if (x < size) {
      x = size;
      vx = -vx;
    } else if (x > 500 - size) {
      x = 500 - size;
      vx = -vx;
    }

    if (y < size) {
      y = size;
      vy = -vy;
    } else if (y > 500 - size) {
      y = 500 - size;
      vy = -vy;
    }
  };
  virtual void updateHP(float dmg) { // dammage taken
  	hp-=dmg;
  }
  virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
    GameObject::getValue(isolate, object);
    object->Set(v8::String::NewFromUtf8(isolate, "_hp_"),
                v8::Number::New(isolate, hp));
  }
};
