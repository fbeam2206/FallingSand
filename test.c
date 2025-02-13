#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#define WIDTH 1200
#define HEIGHT 800
#define ACC 450
#define FRIC 450
#define MAXCOUNT 500
#define RADIUS 20 
#define FLOOR 795

Vector2 zero = {0,0};
Vector2 xUnit = {1,0};
Vector2 yUnit = {0,1};

Rectangle rec = {
  .x = 0,
  .y = 799,
  .width = 1600,
  .height = 2
};

typedef struct sand{
  Vector2 pos;
  Vector2 prevPos;
  Vector2 vel;
  Vector2 dir;
  bool eqaul;
}sand;

typedef struct gameState{
  int grainCount;
  float spawnDelay;
  float spawnTime;
  sand sandarray[MAXCOUNT];
}gameState;

gameState currentState = {
  .grainCount = 0,
  .spawnDelay = 0.05
};

void MainMenu(){

};



void Collision(sand* grain, sand* compGrain){
  int i = 0;
  while(CheckCollisionCircles(grain->pos, RADIUS, compGrain->pos, RADIUS)){
    sand* grain2 = &currentState.sandarray[i];
    i++;
    if(fabs(grain->pos.x - compGrain->pos.x) <= 0.2){
      grain->pos = grain->prevPos;
      grain->vel.y=0;
      return;
    }
    if(CheckCollisionCircles(grain->pos, RADIUS, grain2->pos, RADIUS)){
      grain->dir.y -= 0.1;
      if (grain->dir.y <= 0){grain->dir.y = 0;}
      grain->pos = grain->prevPos;
      grain->vel.y = 0;
      return;
    }
    else if(grain->pos.x - compGrain->pos.x < 0){
      grain->pos.x -= 0.1;
    }
    else if(grain->pos.x - compGrain->pos.x > 0){
      grain->pos.x += 0.1;
    }
  }
}

void UpdatePosition(Texture2D sandTex){
  if(currentState.spawnTime < currentState.spawnDelay){
    currentState.spawnTime += GetFrameTime();
  }
  while(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && currentState.spawnTime > currentState.spawnDelay){
    if(currentState.grainCount >= MAXCOUNT){break;}
    sand grain = {
      .pos = GetMousePosition(),
      .vel.y = 1,
      .dir = {0,1}
    };
    currentState.sandarray[currentState.grainCount++] = grain;
    currentState.spawnTime -= currentState.spawnDelay;
  }
  for(int sandInd=0; sandInd < currentState.grainCount; sandInd++){
    sand *grain = &currentState.sandarray[sandInd];
    grain->prevPos = grain->pos;
    grain->vel.x += ACC*GetFrameTime()*grain->dir.x;
    grain->vel.y += ACC*GetFrameTime()*grain->dir.y;
    grain->pos.x += grain->vel.x*GetFrameTime() + 0.5*ACC*GetFrameTime()*GetFrameTime()*grain->dir.x;
    grain->pos.y += grain->vel.y*GetFrameTime() + 0.5*ACC*GetFrameTime()*GetFrameTime()*grain->dir.y;
    for(int j=0, i = j - 1; j < sandInd; j++){
      sand *compGrain = &currentState.sandarray[j];
      Collision(grain, compGrain);
      if(grain->pos.y > compGrain->pos.y){
        grain->dir.x = 0;
      }
    }
    if(grain->vel.x > 0){
      grain->vel.x -= FRIC*GetFrameTime();
    }
    if(grain->vel.x < 0){
      grain->vel.x += FRIC*GetFrameTime();
    }
    if(-5 <= grain->vel.x <= 5){
      grain->vel.x = 0;
    }
    if(grain->pos.y >= 595 || grain->pos.y == 595){
      grain->pos.y = 595;
      grain->dir.x = 0;
    } 
    //DrawCircle(grain->pos.x, grain->pos.y, 6, BLACK);
    DrawTextureV(sandTex, grain->pos, WHITE);
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
  InitWindow(WIDTH, HEIGHT, "Window");

  Image sandImage = LoadImage("assets/spatialai.png");
  Texture2D sandTex = LoadTextureFromImage(sandImage);

  while(!WindowShouldClose()){
    ClearBackground(WHITE);
    UpdatePosition(sandTex);
    BeginDrawing();
    BeginMode2D(camera);
    EndMode2D();
    EndDrawing();
  }

  UnloadTexture(sandTex);
  CloseWindow();
  return 0;
} 