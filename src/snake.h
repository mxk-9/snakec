#include "raylib.h"
#define MAX_SNAKE_LENGTH (256)
typedef struct Snake {
  int size;
  Vector2 speed;
  Color body;
  Color spots;
  int length;
  Vector2 *segments; /* pointer to array, positions */
} Snake;

enum {
  SNAKE_RED = 1,
  SNAKE_BLUE,
  SNAKE_GREEN,
  SNAKE_DEFAULT,
};


void RotateSnake(Snake *snake);
void SetSnakeSkin(Snake *snake, int skin_number);
