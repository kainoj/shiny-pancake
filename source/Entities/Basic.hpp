#pragma once

struct Basic : public GameObject {
  float hp = 100;
  Basic() : GameObject{"Basic", randRange(1, 2), 0, 0} {}
  virtual void update(float dt) {
    x = (x + 1) % 500;
    y = (y + 1) % 500;
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
