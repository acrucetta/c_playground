#include "main.h"

void Loop();
void Update();
void Draw();

int main(void) {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Pong");

  SetTargetFPS(60); // Set target frames-per-second

  Loop();

  return 0;
}

void Loop() {
  // The main game loop in raylib is really simple - just loop until window
  // should close!
  while (!WindowShouldClose()) {
    Update();
    // Draw or Render - whatever suits you most
    Draw();
  }
}

void Update() {
  // Game rules go here
}

void Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  // Other draw calls would go here.

  EndDrawing();
}
