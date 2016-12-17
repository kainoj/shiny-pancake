#include "World.hpp"
#include "Entities/Basic.hpp"


  std::vector<std::shared_ptr<GameObject> > World::getObjectsInRadius(float x, float y, float radius)
  {
  	std::vector<std::shared_ptr<GameObject> > result;
  	for (auto& object : objects)
  	{
  		float disX = object->x - x;
  		float disY = object->y - y;
  		if(disX*disX + disY*disY < radius*radius)
  		{
  			result.push_back(object);
  		}
  	}
  	return result;
  }

  std::shared_ptr<Basic> World::getNearestUnit(float x, float y, float radius)
  {
  	float minDis = 1000000;
  	std::shared_ptr<Basic> result;
  	for (auto& object : objects)
  	{
	  	auto unit = std::dynamic_pointer_cast<Basic>(object);
	  	if(unit != nullptr)
	  	{
	  		float disX = object->x - x;
  			float disY = object->y - y;
  			if(disX*disX + disY*disY < minDis)
  			{
  				minDis = disX*disX + disY*disY;
  				result = unit;
  			}
	  	}
  	}
  	return result;
  }