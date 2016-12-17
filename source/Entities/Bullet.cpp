#include "Basic.hpp"
#include "Bullet.hpp"

void Bullet::update(float dt) {
  x += velX * dt;
  y += velY * dt;
  if(x > 1920 || x < 0){
  	hp = -1;
  }
  if(y > 1080 || y < 0)
  {
  	hp = -1;
  }
  World& world = World::getInstance();
  auto unit = world.collidesWithUnit(x, y, team);
  if (unit != nullptr) {
    unit->updateHP(damage);
    hp = -1.0f;
  }
}
