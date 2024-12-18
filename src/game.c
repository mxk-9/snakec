#include "game.h"
#include "raylib.h"
#include "stdlib.h"

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
  gm->square_size = 31;
  gm->max_fps = 60;
  gm->frame_counter = 0;
  gm->player_score = 0;

  gm->game_over = false;
  gm->pause = false;
}

void RestartGame(Game *gm, Snake *snake, Food *food) {
  DefaultGameValues(gm);
  GetOffset(gm);
  printf("Offset: %f:%f\n", gm->offset.x, gm->offset.y);

  for (int i = 0; i < gm->max_snake_length; i++) {
    snake->segments[i] = (Vector2){gm->offset.x / 2, gm->offset.y / 2};
  }

  for (int i = 0; i < snake->length; i++) {
    snake->snakePos[i] = (Vector2){0.0f, 0.0f};
  }

  snake->length = 2;
  snake->speed = (Vector2){gm->square_size, 0};
  SetSnakeSkin(snake, GetRandomValue(SNAKE_GREEN, SNAKE_BLUE));
}

void UpdateGame(Game *game, Snake *snake, Food *food) {
  static bool once_print = false;
  if (game->game_over) {
    if (!once_print) {
      printf("Snake is dead\n");
      once_print = !once_print;
    }

    if (IsKeyPressed(KEY_ENTER)) {
      once_print = !once_print;
      RestartGame(game, snake, food);
    }
    return;
  }

  if (IsKeyPressed('P'))
    game->pause = !game->pause;

  if (!game->pause) {
    RotateSnake(snake);

    SnakeMovement(snake, game->frame_counter);

    if (CollisionWithScreen(snake->segments[0], game->screen_width,
                            game->screen_height, game->offset))
      game->game_over = true;

    if (SnakeAteItself(snake))
      game->game_over = true;

    SpawnFood(food, snake->length, snake->segments, game->screen_width,
              game->screen_height, game->offset, game->square_size);

    if (SnakeCollidesFood(snake, food->position, food->size))
      food->active = false;
    ++game->frame_counter;
  }
}

void DrawGame(Game *game, Snake *snake, Food *food) {
  static char *msg_over = "PRESS [ENTER] TO PLAY AGAIN";
  static char *msg_pause = "GAME PAUSED";

  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (game->game_over) {
    DrawText(msg_over, GetScreenWidth() / 2 - MeasureText(msg_over, 20) / 2,
             GetScreenHeight() / 2 - 50, 20, GRAY);
    EndDrawing();
    return;
  }

  DrawGameGrid(game);
  DrawSnake(snake);
  DrawFood(food);

  if (game->pause)
    DrawText(msg_pause, game->screen_width / 2 - MeasureText(msg_pause, 40) / 2,
             game->screen_height / 2 - 40, 40, GRAY);

  EndDrawing();
}

void UnloadGame(Game *gm, Snake *snake) {
  free(snake->segments);
  free(snake->snakePos);
  free(snake);
  free(gm);
}

void GetOffset(Game *gm) {
  gm->offset.x = gm->screen_width % gm->square_size;
  gm->offset.y = gm->screen_height % gm->square_size;
}

void DrawGameGrid(Game *game) {
  for (int i = 0; i < game->screen_width / game->square_size + 1; i++) {
    DrawLineV((Vector2){game->square_size * i + game->offset.x / 2,
                        game->offset.y / 2},
              (Vector2){game->square_size * i + game->offset.x / 2,
                        game->screen_height - game->offset.y / 2},
              LIGHTGRAY);
  }

  for (int i = 0; i < game->screen_height / game->square_size + 1; i++) {
    DrawLineV((Vector2){game->offset.x / 2,
                        game->square_size * i + game->offset.y / 2},
              (Vector2){game->screen_width - game->offset.x / 2,
                        game->square_size * i + game->offset.y / 2},
              LIGHTGRAY);
  }
}

Snake *NewSnake(const int snake_skin_type, Game *game) {
  Snake *snake = malloc(sizeof(Snake));

  snake->speed = (Vector2){game->square_size, 0};
  snake->size = game->square_size;

  SetSnakeSkin(snake, snake_skin_type);

  snake->length = 2;
  snake->segments = malloc(sizeof(Vector2) * game->max_snake_length);
  snake->snakePos = malloc(game->max_snake_length * sizeof(Vector2));

  for (int i = 0; i < game->max_snake_length; i++) {
    snake->segments[i] = (Vector2){game->offset.x / 2, game->offset.y / 2};
  }

  for (int i = 0; i < snake->length; i++) {
    snake->snakePos[i] = (Vector2){0.0f, 0.0f};
  }

  return snake;
}
