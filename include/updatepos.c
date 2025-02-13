#include <collision.c>

void UpdatePosition(){
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
    DrawCircle(grain->pos.x, grain->pos.y, 6, BLACK);
    //DrawTextureV(sandTex, grain->pos, WHITE);
  }
}