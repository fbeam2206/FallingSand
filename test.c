#include <stdio.h>
#include <updatepos.c>

Rectangle rec = {
  .x = 0,
  .y = 799,
  .width = 1600,
  .height = 2
};

void MainMenu(){

};

int main(){

  Camera2D camera = {
    .zoom = 1,
    .offset = zero,
    .target = zero,
    .rotation = 0
  };

  SetTargetFPS(60);
  InitWindow(WIDTH, HEIGHT, "Window");

  Image sandImage = LoadImage("assets/spatialai.png");
  Texture2D sandTex = LoadTextureFromImage(sandImage);

  while(!WindowShouldClose()){
    ClearBackground(WHITE);
    UpdatePosition();
    BeginDrawing();
    BeginMode2D(camera);
    EndMode2D();
    EndDrawing();
  }

  //UnloadTexture(sandTex);
  CloseWindow();
  return 0;
} 