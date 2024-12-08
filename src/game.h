#include "raylib.h"
#include "snake.h"
#include "stdlib.h"

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
void RestartGame(Game *gm, Snake *snake);
void UnloadGame(Game *gm, Snake *snake);
void GetOffset(Game *gm);
Snake *NewSnake(const int snake_skin_type, Game *game);
