#include <cstdlib>
#include <ctime>
#include <cmath>

int randRange(int min, int max) {
  return min + (std::rand() % (max - min + 1));
}

float randFloatRange(float min, float max) {
  return randRange(min * 1000000.0, max * 1000000.0) / 1000000.0;
}

float signum(float x) {
  return x < 0 ? -1.0 : 1.0;
}

float distance(float x1, float y1, float x2, float y2)
{
	float x = x1-x2;
	float y = y1-y2;
	float root = sqrt(x*x + y*y);
	return root;
}