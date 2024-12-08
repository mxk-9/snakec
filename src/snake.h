#include "raylib.h"

typedef struct Snake {
  Vector2 size;
  Color body;
  Color spots;
  int length;
  Vector2 *segments; /* pointer to array */
} Snake;


