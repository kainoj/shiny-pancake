#include "Bullet.hpp"

void Bullet::update(float dt) {
  x += velX * dt;
  y += velY * dt;
  World& world = World::getInstance();
  auto unit = world.collidesWithUnit(x, y, team);
  if (unit != nullptr) {
    // unit->updateHP(damage);
    hp = 0.0f;
  }
}
