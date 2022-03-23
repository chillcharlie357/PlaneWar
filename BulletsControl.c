//
// Created by lenovo on 2022/1/19.
//

#include "BulletsControl.h"

Bullet *Bullet_Create(int x, int y, int w, int h,int speedX, int speedY,int exist,int type){
    Bullet *bullet = malloc(sizeof(Bullet));
    bullet->rect.x = x;
    bullet->rect.y = y;
    bullet->rect.w = w;
    bullet->rect.h = h;
    bullet->speedX = speedX;
    bullet->speedY = speedY;
    bullet->exist = exist;
    bullet->type = type;
    bullet->damage = 1;
    return bullet;
}

void Bullet_Move(Bullet *self){
    if(self->exist){
        self->rect.x += self->speedX;
        self->rect.y += self->speedY;
        if(self->rect.x <= 0 && self->speedX < 0 || self->rect.x >= WindowY && self->speedX > 0){
            self->speedX *= -1;
        }
    }
    if(self->rect.y <= -self->rect.h || self->rect.y >= WindowY){
        self->exist = 0;
    }
}

void Bullet_FMove(Bullet *self){

}

void Bullet_Draw(Bullet *self,SDL_Renderer *renderer){
    if(self->exist != 0){
        SDL_RenderCopy(renderer, Resource_GetTexture(self->type),NULL,&self->rect);
    }
}

void Bullet_Destroy(Bullet *self){
    free(self);
}

///Attach a Bullet to rect;
void Bullet_Load(int x, int y, Bullet *bullets){
    if (!bullets->exist){
        bullets->rect.x = x;
        bullets->rect.y = y;
        bullets->exist = 1;
    }
}
