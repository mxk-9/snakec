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

void SetSnakeSkin(Snake *snake, const int skin_number) {
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

void DrawSnake(const Snake *snake) {
  for (int i = 0; i < snake->length; i++) {
    DrawRectangleV(snake->segments[i], (Vector2){snake->size, snake->size},
                   snake->body);
    DrawRectangleLinesEx(
        (Rectangle){
            snake->segments[i].x,
            snake->segments[i].y,
            snake->size,
            snake->size,
        },
        5, snake->spots);
  }
}

void SnakeMovement(Snake *snake, const int frame_counter) {
  for (int i = 0; i < snake->length; i++) {
      snake->snakePos[i] = snake->segments[i];
    }

    if ((frame_counter % 5) == 0) {
      for (int i = 0; i < snake->length; i++) {
        if (i == 0) {
          snake->segments->x += snake->speed.x;
          snake->segments->y += snake->speed.y;
        } else {
          snake->segments[i] = snake->snakePos[i - 1];
        }
      }
    }
}

bool SnakeAteItself(const Snake *snake) {
  bool snake_dead = false;
  for (int i = 1; i < snake->length; i++)
    if ((snake->segments->x == snake->segments[i].x) &&
        (snake->segments->y == snake->segments[i].y)) {
      snake_dead = true;
      printf("Snake eats itself\n");
      break;
    }
  return snake_dead;
}


bool SnakeCollidesFood(Snake *snake, const Vector2 food_pos, const int food_size) {
  bool collide = false;
  if ((snake->segments->x < (food_pos.x + food_size)) &&
        ((snake->segments->x + snake->size) > food_pos.x) &&
        (snake->segments->y < (food_pos.y + food_size)) &&
      ((snake->segments->y + snake->size) > food_pos.y)) {
    
      snake->segments[snake->length] = snake->snakePos[snake->length - 1];
      ++snake->length;
      collide = true;
  }

  return collide;
}
