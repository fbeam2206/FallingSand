#ifndef SAND_H
#define SAND_H

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#define WIDTH 1200
#define HEIGHT 800
#define ACC 450
#define FRIC 450
#define MAXCOUNT 500
#define RADIUS 6
#define FLOOR 795
#define FONT_SIZE 48

#ifndef zero
  #define zero {0,0}
#endif
#ifndef xUnit
  #define xUnit {1,0}
#endif
#ifndef yUnit
  #define yUnit {0,1}
 #endif

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

void Collision(sand* grain, sand* compGrain);

void UpdatePosition();

#endif