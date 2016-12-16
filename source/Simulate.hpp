#include "World.hpp"
#include "Spawner.hpp"
#include <memory>
#include <cstdlib>
#include <ctime>

void initWorld() {
  std::srand(time(nullptr));
  World &world = World::getInstance();
  auto spawner = std::make_shared<Spawner>(1.0f);
  spawner->x = 100;
  spawner->y = 100;
  world.spawn(spawner);
}

v8::Local<v8::Array> simulate(v8::Isolate *isolate) {
  World &world = World::getInstance();
  world.step();

  v8::Local<v8::Array> data = v8::Array::New(isolate, world.objects.size());
  size_t index = 0;
  for (auto &go : world.objects) {
    auto jsObject = go->getData(isolate);
    data->Set(index++, jsObject);
  }
  return data;
}
