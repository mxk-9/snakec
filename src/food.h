#include "raylib.h"
#include "stdlib.h"

typedef struct Food {
  bool active;
  Color color;
  Vector2 position;
  int size;
} Food;

Food *NewFood(int size, Color color);
