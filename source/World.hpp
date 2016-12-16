#pragma once
#include "GameObject.hpp"

struct World{
	static World &getInstance()
	{
		static World goFactory;
		return goFactory;
	}
	std::vector<std::shared_ptr<GameObject> > objects;
	int currentObjectID = 0;
	void spawn(std::shared_ptr<GameObject> go)
	{
		go->id = ++currentObjectID;
		objects.push_back(go);
	}
	void step()
	{
		float dt = 1.0f/60;
		for(auto& go : objects)
		{
			go->update(dt);
		}
	}
};