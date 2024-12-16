#include "food.h"

Food *NewFood(int size, Color color) {
  Food *food = malloc(sizeof(Food));
  food->size = size;
  food->color = color;
  food->active = false;
  return food;
}
