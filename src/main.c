#include "game.h"
#include "raylib.h"
/* #include "stdio.h" */

int main(void) {
  Game *game = InitGame();

  Snake *snake = NewSnake(GetRandomValue(SNAKE_RED, SNAKE_GREEN), game);

  Food *food = NewFood(game->square_size, ORANGE);

  InitWindow(game->screen_width, game->screen_height, "Snake on C");
  SetTargetFPS(game->max_fps);

  printf("Initialisation complete, launching game...\n");
  while (!WindowShouldClose()) {
    UpdateGame(game, snake, food);
    DrawGame(game, snake, food);
  }

  UnloadGame(game, snake);
  CloseWindow();
}
