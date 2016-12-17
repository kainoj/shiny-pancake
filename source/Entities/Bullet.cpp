#include "Basic.hpp"
#include "Bullet.hpp"

void Bullet::update(float dt) {
  x = x + velX * dt;
  y = y + velY * dt;
  if (x > 1920 || x < 0) {
    hp = -1;
    return;
  }
  if (y > 1080 || y < 0) {
    hp = -1;
    return;
  }
  World& world = World::getInstance();
  auto unit = world.collidesWithUnit(x, y, team);
  if (unit != nullptr) {
    unit->updateHP(damage);
    hp = -1.0f;
  }
}
