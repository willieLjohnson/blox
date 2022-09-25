#include "raylib.h"
#include <iostream>

#define PLAYER_LIFES 5
#define BRICKS_LINES 5
#define BRICKS_PER_LINE 20

#define BRICKS_POSITION_Y 50

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Player {
  Vector2 position;
  Vector2 speed;
  Vector2 size;
  Rectangle bounds;
  int lifes;
} Player;

typedef struct Ball {
  Vector2 position;
  Vector2 speed;
  int radius;
  bool active;
} Ball;

typedef struct Brick {
  Vector2 position;
  Vector2 size;
  Rectangle bounds;
  int resistance;
  bool active;
} Brick;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BLOX");

  GameScreen screen = LOGO;

  int framesCounter = 0;
  int gameResult = -1;
  bool gamePaused = false;

  // Game objects
  Player player = {0};
  Ball ball = {0};
  Brick bricks[BRICKS_LINES][BRICKS_PER_LINE] = {0};

  player.position = (Vector2){screenWidth / 2, screenHeight * 7 / 8};
  player.speed = (Vector2){8.0f, 0.0f};
  player.size = (Vector2){100, 24};
  player.lifes = PLAYER_LIFES;

  ball.radius = 10.0f;
  ball.active = false;
  ball.position = (Vector2){player.position.x + player.size.x / 2,
                            player.position.y - ball.radius * 2};
  ball.speed = (Vector2){4.0f, 4.0f};

  // Create bricks
  for (int j = 0; j < BRICKS_LINES; j++) {
    for (int i = 0; i < BRICKS_PER_LINE; i++) {
      bricks[j][i].size = (Vector2){screenWidth / BRICKS_PER_LINE, 20};
      bricks[j][i].position = (Vector2){
          i * bricks[j][i].size.x, j * bricks[j][i].size.y + BRICKS_POSITION_Y};
      bricks[j][i].bounds =
          (Rectangle){bricks[j][i].position.x, bricks[j][i].position.y,
                      bricks[j][i].size.x, bricks[j][i].size.y};
      bricks[j][i].active = true;
    }
  }

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    switch (screen) {
    case LOGO:
      framesCounter++;
      if (framesCounter > 180) {
        screen = TITLE;
        framesCounter = 0;
      }
      break;
    case TITLE:
      framesCounter++;
      if (IsKeyPressed(KEY_ENTER))
        screen = GAMEPLAY;
      break;
    case GAMEPLAY:
      if (!gamePaused) {
        // logic
      }
      break;
    case ENDING:
      framesCounter++;
      if (IsKeyPressed(KEY_ENTER))
        screen = TITLE;
      break;
    default:
      break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (screen) {
    case LOGO:
      DrawText("LT GAMES", 20, 20, 40, LIGHTGRAY);
      break;
    case TITLE:
      DrawText("BLOX", 20, 20, 40, DARKGREEN);
      if ((framesCounter / 30) % 2 == 0)
        DrawText("PRESS [ENTER] to START",
                 GetScreenWidth() / 2 -
                     MeasureText("PRESS [ENTER] to START", 20) / 2,
                 GetScreenHeight() / 2 + 60, 20, DARKGRAY);

      break;
    case GAMEPLAY:
      DrawRectangle(player.position.x, player.position.y, player.size.x,
                    player.size.y, BLACK);
      DrawCircleV(ball.position, ball.radius, MAROON);

      // Bricks
      for (int j = 0; j < BRICKS_LINES; j++) {
        for (int i = 0; i < BRICKS_PER_LINE; i++) {
          if (bricks[j][i].active) {
            if ((i + j) % 2 == 2)
              DrawRectangle(bricks[j][i].position.x, bricks[j][i].position.y,
                            bricks[j][i].size.x, bricks[j][i].size.y, GRAY);
            else
              DrawRectangle(bricks[j][i].position.x, bricks[j][i].position.y,
                            bricks[j][i].size.x, bricks[j][i].size.y, GRAY);
          }
        }
      }

      // player lives
      for (int i = 0; i < player.lifes; i++)
        DrawRectangle(20 + 40 * i, screenHeight - 30, 35, 10, LIGHTGRAY);
      if (gamePaused)
        DrawText("GAME PAUSED",
                 screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2,
                 screenHeight / 2 + 60, 40, GRAY);

      break;
    case ENDING:
      DrawText("ENDING", 20, 20, 40, DARKBLUE);
      if ((framesCounter / 3) % 2 == 0)
        DrawText("PRESS [ENTER] TO PLAY AGAIN",
                 GetScreenWidth() / 2 -
                     MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
                 GetScreenHeight() / 2 + 80, 20, GRAY);
      break;
    default:
      break;
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
