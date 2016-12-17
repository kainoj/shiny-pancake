#pragma once

#include "Stats.hpp"
#include "World.hpp"

struct Stats : public GameObject {
  Stats() : GameObject("Stats", 0, 0, 0, 0) { hp = 1; }
  void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
    float team1 = 0;
    float team2 = 0;
    float team3 = 0;
    float team4 = 0;

    World& world = World::getInstance();

    for (auto& object : world.objects) {
      unsigned score = object->score();
      switch (object->team) {
        case 1:
          team1 += score;
          break;
        case 2:
          team2 += score;
          break;
        case 3:
          team3 += score;
          break;
        case 4:
          team4 += score;
          break;
      }
    }

    float sum = team1 + team2 + team3 + team4;

    team1 /= sum;
    team2 /= sum;
    team3 /= sum;
    team4 /= sum;

    v8::Local<v8::Object> stats = v8::Object::New(isolate);

    stats->Set(v8::String::NewFromUtf8(isolate, "team1"),
               v8::Number::New(isolate, team1));
    stats->Set(v8::String::NewFromUtf8(isolate, "team2"),
               v8::Number::New(isolate, team2));
    stats->Set(v8::String::NewFromUtf8(isolate, "team3"),
               v8::Number::New(isolate, team3));
    stats->Set(v8::String::NewFromUtf8(isolate, "team4"),
               v8::Number::New(isolate, team4));

    object->Set(v8::String::NewFromUtf8(isolate, "stats"), stats);

    GameObject::getValue(isolate, object);
  }
};
