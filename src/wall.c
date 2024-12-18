#include "wall.h"

bool CollisionWithScreen(Vector2 snake, int scr_w, int scr_h, Vector2 offset) {
  bool game_over = false;

  if (snake.x > (scr_w - offset.x) || snake.y > (scr_h - offset.y) ||
      (snake.x < 0) || (snake.y < 0)) {
    game_over = true;
    printf("Snake hits the wall:\n\
Head:\t\t% 4.2f :% 4.2f\n\
Wall max:\t% 4.2f :% 4.2f\n",
           snake.x, snake.y, (scr_w - offset.x), (scr_h - offset.y));
  }

  return game_over;
}
