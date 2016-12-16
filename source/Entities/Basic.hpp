#pragma once

#include <cmath>

struct Basic : public GameObject {
  float hp = 100;
  float vx = randRange(-10, 10) * 20;
  float vy = randRange(-10, 10) * 20;
  Basic() : GameObject{"Basic", randRange(1, 2), 0, 0} {}
  virtual void update(float dt) {
    x = (int) (x + vx * dt);
    y = (int) (y + vy * dt);

    if (x < 0) {
      x = 0;
      vx = -vx;
    } else if (x > 500) {
      x = 500;
      vx = -vx;
    }

    if (y < 0) {
      y = 0;
      vy = -vy;
    } else if (y > 500) {
      y = 500;
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
