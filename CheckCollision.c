//
// Created by lenovo on 2022/1/20.
//

#include "CheckCollision.h"

int Collision_Check(SDL_Rect A,SDL_Rect B){
    if(A.x >= B.x + B.w){
        return 0;
    }
    if(A.x + A.w <= B.x){
        return 0;
    }
    if(A.y >= B.y + B.h){
        return 0;
    }
    if(A.y + A.h <= B.y){
        return 0;
    }
    return 1;
}