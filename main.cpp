#include "raylib.h"

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "BLOX");

  GameScreen screen = LOGO;

  int framesCounter = 0;
  int gameResult = -1;
  bool gamePaused = false;

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
    {
      ClearBackground(RAYWHITE);
      switch (screen) {
      case LOGO:
        DrawText("LT GAMES", 20, 20, 40, LIGHTGRAY);
        break;
      case TITLE:

        DrawText("BLOX", 20, 20, 40, DARKGREEN);
        break;
      case GAMEPLAY:
        DrawText("PLAY", 20, 20, 40, MAROON);
        break;
      case ENDING:
        DrawText("ENDING", 20, 20, 40, DARKBLUE);
        break;
      default:
        break;
      }
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
