#include "GameObject.hpp"

class Bullet
{
	Bullet() : GameObject{"Bullet", 0, 0, 0} 
	int damage;
	int armorPen;
	float velX = 0.0, velY = 0.0;
	virtual void update(float dt){
		x += velX * dt;
		y += velY * dt;
	};
  virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
  	GameObject::getValue(isolate, object);
  	
  }
};