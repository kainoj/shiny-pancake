#include <v8.h>
#include <string>
#include "utilities.hpp"
#pragma once

struct GameObject {
  float x;
  float y;
  int size; 
  unsigned team;
  std::string type;
  unsigned id;
  GameObject(std::string type_, unsigned team_, float x_, float y_, int size_)
      : x(x_), y{y_}, size{size_}, type{type_}, team{team_}, id{0} {}
  v8::Local<v8::Object> getData(v8::Isolate* isolate) {
    v8::Local<v8::Object> object = v8::Object::New(isolate);
    getValue(isolate, object);
    return object;
  }
  virtual void update(float dt){};
  virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
    object->Set(v8::String::NewFromUtf8(isolate, "_id_"),
                v8::Number::New(isolate, id));
    object->Set(v8::String::NewFromUtf8(isolate, "posx"),
                v8::Number::New(isolate, x));
    object->Set(v8::String::NewFromUtf8(isolate, "posy"),
                v8::Number::New(isolate, y));
    object->Set(v8::String::NewFromUtf8(isolate, "team"),
                v8::Number::New(isolate, team));
    object->Set(v8::String::NewFromUtf8(isolate, "type"),
                v8::String::NewFromUtf8(isolate, type.c_str()));
  }
};
