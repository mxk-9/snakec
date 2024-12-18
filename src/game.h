#include "raylib.h"
#include "snake.h"
#include "wall.h"
#include "food.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct Game {
  int max_snake_length;
  int square_size;
  int max_fps;
  int screen_width;
  int screen_height;
  int frame_counter;
  int player_score;
  bool pause;
  bool game_over;
  Vector2 offset;
} Game;

Game *InitGame();
void DefaultGameValues(Game *gm);
void RestartGame(Game *gm, Snake *snake, Food *food);
void UpdateGame(Game *game, Snake *snake, Food *food);
void UnloadGame(Game *gm, Snake *snake);
void GetOffset(Game *gm);

void DrawGame(Game *game, Snake *snake, Food *food);
void DrawGameGrid(Game *game);

Snake *NewSnake(const int snake_skin_type, Game *game);
