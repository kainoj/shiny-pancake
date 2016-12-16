#pragma once
#include "GameObject"

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
}