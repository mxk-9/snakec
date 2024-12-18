#include "raylib.h"
#include "stdlib.h"

typedef struct Food {
  bool active;
  Color color;
  Vector2 position;
  int size;
} Food;

Food *NewFood(const int size, const Color color);
void DrawFood(const Food *food);
void SpawnFood(Food *food, const int length, const Vector2 *segments,
               const int scr_w, const int scr_h, const Vector2 offset,
               const int square_size);
