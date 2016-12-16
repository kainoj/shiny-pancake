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

    if (x < 10) {	// kuleczki odbijaja sie krawedzia
      x = 10;
      vx = -vx;
    } else if (x > 490) {
      x = 490;
      vx = -vx;
    }

    if (y < 10) {
      y = 10;
      vy = -vy;
    } else if (y > 490) {
      y = 490;
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
