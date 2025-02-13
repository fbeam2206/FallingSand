#include <sand.h>
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
