//
// Created by lenovo on 2022/1/18.
//

#include "Plane.h"

Plane * Plane_Create(int x,int y,int w,int h,int speedX,int speedY,int type){
    Plane *p = malloc(sizeof(Plane));
    p->rect.x = x;
    p->rect.y = y;
    p->rect.w = w;
    p->rect.h = h;
    p->speedX = speedX;
    p->speedY = speedY;
    p->alive = 1;
    p->bullet_damage_increase = 1;
    p->have_shield = 0;
    p->special_attack = 0;
    p->type = type;
    return p;
}

void Plane_Draw(Plane *self,SDL_Renderer *renderer){
    if(self->alive){
        SDL_RenderCopy(renderer, Resource_GetTexture(self->type),NULL,&(self->rect));
        if(self->have_shield){
            SDL_RenderCopy(renderer, Resource_GetTexture(14),NULL,&(self->rect));
        }
    }
}

void Plane_Destroy(Plane *self){
    free(self);
}
