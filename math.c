#include <stdio.h>
#include <unistd.h>
#include <raylib.h>
#include <raymath.h>

int main(){
  Vector2 vec1, vec2, resultVec;
  float result;
  char ans;
  int op;

  printf("Enter (x1,y1) (x2,y2)\n");
  scanf("%f %f %f %f", &vec1.x, &vec1.y, &vec2.x, &vec2.y);

here:

  printf("1. Subtract 2. Add 3. Angle 4. CosAngle 5. SinAngle\n");
  scanf(" %d", &op);

  if(op==1){
  resultVec = Vector2Subtract(vec1, vec2);
  printf("(%f, %f)\n", resultVec.x, resultVec.y);
  }

  if(op==2){
  resultVec = Vector2Add(vec1, vec1);
  printf("(%f, %f)\n", resultVec.x, resultVec.y);
  }

  if(op==3){
  result = Vector2LineAngle(Vector2Normalize(vec1), Vector2Normalize(vec2));
  printf("(%f)\n", result);
  }

  if(op==4){
  result = cos(Vector2LineAngle(Vector2Normalize(vec1), Vector2Normalize(vec2)));
  printf("(%f)\n", result);
  }

  if(op==5){
  result = sin(Vector2LineAngle(Vector2Normalize(vec1), Vector2Normalize(vec2)));
  printf("(%f)\n", result);
  }

  printf("Another operation? y/n\n");
  scanf(" %c", &ans);
  if(ans == 'y'){
    goto here;
  }

  return 0;
}