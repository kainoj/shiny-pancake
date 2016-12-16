#pragma once

struct Basic : public GameObject {
  Basic() : GameObject{"Basic", randRange(1, 2), 0, 0} {}
  virtual void update(float dt) {
    x = (x + 1) % 500;
    y = (y + 1) % 500;
  };
  virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
    GameObject::getValue(isolate, object);
  }
};
