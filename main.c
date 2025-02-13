#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#define WINDOW_WIDTH 800
#define WINDOW_HIEGHT 600
#define MAX_PARTICLES 1000
#define ACC 90

typedef struct Sand
{
  Vector2 dir;
  Vector2 pos;
  Vector2 prevPos;
  Vector2 vel;
}Sand;

typedef struct State
{
  float spawnDelay;
  float spawnTime;
  int sandCount;
  Sand sands[MAX_PARTICLES]; // Array of Sand Structs
}State;

const State DefaultState = {
  .spawnDelay = 0.1f
};

int main()
{
  State currentState = DefaultState;
  SetTargetFPS(144);

  struct Camera2D camera =
  {
    .offset = {0},
    .target = (Vector2){0,0},
    .rotation = 0,
    .zoom = 1
  };

  struct Rectangle floor = 
  {
    .x = 0,
    .y = 400,
    .width = 800,
    .height = 10
  };

  InitWindow(WINDOW_WIDTH, WINDOW_HIEGHT, "Falling Sand");

  while(!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawLine(0, 500, 800, 500, BLACK);
      DrawCircle(0, 0, 5, YELLOW);
      DrawCircle(800, 0, 5, BLUE);
      DrawCircle(0, 595, 5, BLACK);
      if(currentState.spawnTime < currentState.spawnDelay)
      {
        currentState.spawnTime += GetFrameTime();
      }
      while(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && currentState.spawnTime >= currentState.spawnDelay)
      {
        if(currentState.sandCount >= MAX_PARTICLES){break;}
        Sand sand = 
        {
          .pos = GetMousePosition(),
          .vel.y = 0.01
        };
        currentState.sands[currentState.sandCount++] = sand;
        currentState.spawnTime -= currentState.spawnDelay;
      }

      BeginMode2D(camera);
        for(int sandInd=0; sandInd < currentState.sandCount; sandInd++)
        {
          Sand *grain = &currentState.sands[sandInd];
          grain->vel.y += ACC * GetFrameTime();
          grain->prevPos = grain->pos;
          grain->pos.y += grain->vel.y;

          for(int j=0; j < sandInd; j++)
          {
            Sand *testGrain = &currentState.sands[j];
            if(CheckCollisionCircles(grain->pos, 5, testGrain->pos, 5))
            {
              grain->pos = grain->prevPos;
              grain->vel.y = 0;
            }
          }
          if(grain->pos.y >= 500)
          {grain->pos.y = 498.5;}
          DrawCircle(grain->pos.x, grain->pos.y, 5, RED);
        }
      EndMode2D();
      EndDrawing();
  }

  CloseWindow();
  return 0;
}
