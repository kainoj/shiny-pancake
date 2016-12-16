#include "World.hpp"
#include <memory>

void initWorld(){
	World& world = World::getInstance();
	for(int i = 0;i < 10; i++){
		auto ball = std::make_shared<Ball>();\
		ball->x = 10 + 30*i;
		ball->y = 20 + 40*i;
		world.spawn(ball);
	}
}

v8::Local<v8::Array> simulate(v8::Isolate* isolate)
{
	World& world = World::getInstance();
	world.step();

	v8::Local<v8::Array> data = v8::Array::New(isolate, 1);
	size_t index = 0;
	for(auto& go : world.objects)
	{
		auto jsObject = go->getData(isolate);
		data->Set(index++, jsObject);
	}
	return data;
}