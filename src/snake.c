#include "snake.h"
#include "raylib.h"

void RotateSnake(Snake *snake) {
  if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0)) {
    snake->speed = (Vector2){snake->size, 0};
  }
  if (IsKeyPressed(KEY_LEFT) && (snake->speed.x == 0)) {
    snake->speed = (Vector2){-snake->size, 0};
  }
  if (IsKeyPressed(KEY_UP) && (snake->speed.y == 0)) {
    snake->speed = (Vector2){0, -snake->size};
  }
  if (IsKeyPressed(KEY_DOWN) && (snake->speed.y == 0)) {
    snake->speed = (Vector2){0, snake->size};
  }
}

void SetSnakeSkin(Snake *snake, int skin_number) {
  switch (skin_number) {
  case 1:
    snake->body = PINK;
    snake->spots = RED;
    break;
  case 2:
    snake->body = SKYBLUE;
    snake->spots = BLUE;
    break;
  case 3:
    snake->body = GREEN;
    snake->spots = LIME;
    break;
  default:
    snake->body = DARKGREEN;
    snake->spots = GREEN;
    break;
  }
}
