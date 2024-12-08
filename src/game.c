#include "game.h"

Game *InitGame() {
  Game *game = malloc(sizeof(Game));

  DefaultGameValues(game);

  game->screen_width = 800;
  game->screen_height = 800;

  GetOffset(game);

  return game;
}

void DefaultGameValues(Game *gm) {
  gm->max_snake_length = 100;
  gm->square_size = 10;
  gm->max_fps = 60;
  gm->frame_counter = 0;
  gm->player_score = 0;

  gm->game_over = false;
  gm->pause = false;
}

void RestartGame(Game *gm, Snake *snake) {
  DefaultGameValues(gm);
  GetOffset(gm);

  snake->length = 2;
}

void UnloadGame(Game *gm, Snake *snake) {
  free(snake->segments);
  free(snake);
  free(gm);
}

void GetOffset(Game *gm) {
  gm->offset.x = gm->screen_width % gm->square_size;
  gm->offset.y = gm->screen_height % gm->square_size;
}

Snake *NewSnake(const int snake_skin_type, Game *game) {
  Snake *snake = malloc(sizeof(Snake));

  snake->size.x = game->square_size;
  snake->size.y = game->square_size;

  switch (snake_skin_type) {
  case 1:
    snake->body = PINK;
    snake->spots = RED;
    break;
  case 2:
    snake->body = BLUE;
    snake->spots = SKYBLUE;
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

  snake->length = 2;
  snake->segments = malloc(sizeof(Vector2) * game->max_snake_length);

  return snake;
}
