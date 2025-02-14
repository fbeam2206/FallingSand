#include <stdio.h>
#include <updatepos.c>

Rectangle rec = {
  .x = 0,
  .y = 799,
  .width = 1600,
  .height = 2
};


void MainMenu(Camera2D camera){
  Vector2 clickCord = {0,0};
  int menuWidth = MeasureText("MENU", 48);
  int startWidth = MeasureText("START", 48);
  int optionsWidth = MeasureText("OPTIONS", 48);
  int quitWidth = MeasureText("QUIT", 48);

  Rectangle button = {
    .x = WIDTH/2 - menuWidth/2,
    .y = HEIGHT/14,
    .width = menuWidth + 2,
    .height = HEIGHT/18
  };

  Rectangle button2 = {
    .x = WIDTH/2 - startWidth/2,
    .y = button.y + button.height * 1.5,
    .width = startWidth + 3,
    .height = button.height
  };

  Rectangle button3 = {
    .x = WIDTH/2 - optionsWidth/2,
    .y = button2.y + button2.height * 1.5,
    .width = optionsWidth + 2,
    .height = button2.height
  };

  Rectangle button4 = {
    .x = WIDTH/2 - quitWidth/2,
    .y = button3.y + button2.height * 1.5,
    .width = quitWidth + 3,
    .height = button2.height
  };

  while(!WindowShouldClose()){
  BeginDrawing();
  BeginMode2D(camera);
  ClearBackground(BLACK);
    clickCord = GetMousePosition();
    DrawRectangle(button.x, button.y, button.width, button.height, RAYWHITE);
    DrawText("MENU", button.x + 1, button.y, 48, BLACK);
    DrawRectangle(button2.x, button2.y, button2.width, button2.height, RAYWHITE);
    DrawText("START", button2.x + 1, button2.y, 48, BLACK);
    DrawRectangle(button3.x, button3.y, button3.width, button3.height, RAYWHITE);
    DrawText("OPTIONS", button3.x + 1, button3.y, 48, BLACK);
    DrawRectangle(button4.x, button4.y, button4.width, button4.height, RAYWHITE);
    DrawText("QUIT", button4.x + 1, button4.y, 48, BLACK);
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      if(CheckCollisionPointRec(clickCord, button2))
        break;
      //if(CheckCollisionpointRec(clickCord, button3))
      if(CheckCollisionPointRec(clickCord, button4)){
        CloseWindow();
        break;
      }
    }
  EndMode2D();
  EndDrawing();
  }
};

int main(){

  Camera2D camera = {
    .zoom = 1,
    .offset = zero,
    .target = zero,
    .rotation = 0
  };

  SetTargetFPS(60);
  GetFontDefault();
  InitWindow(WIDTH, HEIGHT, "Window");
  MainMenu(camera);
  //Image sandImage = LoadImage("assets/spatialai.png");
  //Texture2D sandTex = LoadTextureFromImage(sandImage);

  while(!WindowShouldClose()){
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(WHITE);
    UpdatePosition();
    EndMode2D();
    EndDrawing();
  }
  END:
  //UnloadTexture(sandTex);
  CloseWindow();
  return 0;
} 