#include "World.hpp"
#include "Entities/Spawner.hpp"
#include "Entities/Basic.hpp"
#include "Stats.hpp"
#include <memory>
#include "consts.hpp"

void initWorld() {
  std::srand(time(nullptr));
  World &world = World::getInstance();

  auto stats = std::make_shared<Stats>();
  world.spawn(stats);

  auto spawner1 = std::make_shared<Spawner>(1.0f, 1, SniperCd1, TankCd1);
  spawner1->x = 50;
  spawner1->y = 80;
  world.spawn(spawner1);

  auto spawner2 = std::make_shared<Spawner>(1.0f, 2, SniperCd2, TankCd2);
  spawner2->x = world.worldSizeX - 50;
  spawner2->y = world.worldSizeY - 50;
  world.spawn(spawner2);

  auto spawner3 = std::make_shared<Spawner>(1.0f, 3, SniperCd3, TankCd3);
  spawner3->x = world.worldSizeX - 50;
  spawner3->y = 80;
  world.spawn(spawner3);

  auto spawner4 = std::make_shared<Spawner>(1.0f, 4, SniperCd4, TankCd4);
  spawner4->x = 50;
  spawner4->y = world.worldSizeY - 50;
  world.spawn(spawner4);
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
  world.removeObjects();
  return data;
}
