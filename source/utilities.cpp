#include <cstdlib>
#include <ctime>

int randRange(int min, int max) {
  return min + (std::rand() % (max - min + 1));
}

float randFloatRange(float min, float max) {
  return randRange(min*1000000.0, max*1000000.0)/1000000.0;
}