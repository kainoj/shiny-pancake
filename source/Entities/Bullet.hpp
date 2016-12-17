#include "../GameObject.hpp"
#include "../World.hpp"
#include <cmath>

struct Bullet : public GameObject{
	Bullet(unsigned team, float speed, float x, float y) : GameObject{"Bullet", team, 0, 0, 0} 
	{
		float root = sqrt(x*x + y*y);
		velX = (x/root) * speed;
		velY = (y/root) * speed;
	}
	float damage = 10.0f;
	float armorPen;
	float velX = 0.0, velY = 0.0;
	virtual void update(float dt);
  virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
  	GameObject::getValue(isolate, object);
  }
};