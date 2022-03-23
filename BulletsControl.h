//
// Created by lenovo on 2022/1/19.
//

#ifndef PROJECT_2_BULLETSCONTROL_H
#define PROJECT_2_BULLETSCONTROL_H

#include <SDL2/SDL.h>
#include "Resource.h"
#include "Config.h"

typedef struct {
    SDL_Rect rect;
    int damage;
    int speedX,speedY;
    int exist;
    int type;
} Bullet;

Bullet *Bullet_Create(int x, int y, int w, int h,int speedX, int speedY,int exist,int type);
void Bullet_Move(Bullet *self);
void Bullet_FMove(Bullet *self);
void Bullet_Draw(Bullet *self,SDL_Renderer *renderer);
void Bullet_Destroy(Bullet *self);
void Bullet_Load(int x, int y, Bullet *bullets);

#endif //PROJECT_2_BULLETSCONTROL_H
