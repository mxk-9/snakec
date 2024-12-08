#include "game.h"
/* #include "stdio.h" */

typedef struct Food {
  bool active;
  Color color;
  Vector2 position;
  Vector2 size;
} Food;

int main(void) {
  Game *game = InitGame();

  Snake *snake = NewSnake(1, game);

  InitWindow(game->screen_width, game->screen_height, "Snake");
  SetTargetFPS(game->max_fps);

  while (!WindowShouldClose()) {
    BeginDrawing();
    EndDrawing();
  }

  UnloadGame(game, snake);
  CloseWindow();
}


