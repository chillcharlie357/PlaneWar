//
// Created by lenovo on 2022/1/18.
//

#ifndef PROJECT_2_PLANE_H
#define PROJECT_2_PLANE_H
#include <SDL2/SDL.h>
#include "Resource.h"
#include "Config.h"

///0 Player,1 Enemy1, 2 Enemy2, 3 Enemy3
typedef struct {
    SDL_Rect rect;
    int speedX,speedY;
    int alive;
    int type;
    int hp;
    int bullet_damage_increase;
    int have_shield;
    int special_attack;
} Plane;

Plane * Plane_Create(int x,int y,int w,int h,int speedX,int speedY,int type);
void Plane_Draw(Plane *self,SDL_Renderer *renderer);
void Plane_Destroy(Plane *self);

#endif //PROJECT_2_PLANE_H
