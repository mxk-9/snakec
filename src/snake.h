#include "raylib.h"
#include "stdio.h"

typedef struct Snake {
  int size;
  Vector2 speed;
  Color body;
  Color spots;
  int length;
  Vector2 *segments;
  Vector2 *snakePos;
} Snake;

enum {
  SNAKE_RED = 1,
  SNAKE_BLUE,
  SNAKE_GREEN,
  SNAKE_DEFAULT,
};


void RotateSnake(Snake *snake);
void SetSnakeSkin(Snake *snake, const int skin_number);
void DrawSnake(const Snake *snake);
void SnakeMovement(Snake *snake, const int frame_counter);
bool SnakeAteItself(const Snake *snake);
bool SnakeCollidesFood(Snake *snake, const Vector2 food_pos, const int food_size);
