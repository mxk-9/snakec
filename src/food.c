#include "food.h"

Food *NewFood(const int size, const Color color) {
  Food *food = malloc(sizeof(Food));
  food->size = size;
  food->color = color;
  food->active = false;
  return food;
}

void DrawFood(const Food *food) {
  DrawRectangleV(food->position, (Vector2){food->size, food->size},
                 food->color);
}

void SpawnFood(Food *food, const int length, const Vector2 *segments,
               const int scr_w, const int scr_h, const Vector2 offset,
               const int square_size) {
  if (!food->active) {
    food->active = true;

    // Spawn food until it won't collides with snake
    bool equ = false;
    for (int i = 0; i < length; i++) {
      do {
        food->position = (Vector2){
            GetRandomValue(0, (scr_w / square_size) - 1) *
                    square_size +
                offset.x / 2,
            GetRandomValue(0, (scr_h / square_size) - 1) *
                    square_size +
                offset.y / 2};
        i = 0;
        equ = ((food->position.x == segments[i].x) ||
               (food->position.y == segments[i].y));
      } while (equ);
      if (!equ)
        break;
    }
  }
}
