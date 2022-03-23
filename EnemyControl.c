//
// Created by lenovo on 2022/1/19.
//

#include "EnemyControl.h"

Plane *Enemy_Create(int level){
    int x = rand() % (WindowX - 197);
    int y = - rand() % 6000;
    Plane *p;
    if(level == 1 || level == 2){
        p = Plane_Create(x,y,197,134,10,3,level + 1);
        p->hp = 1;
    } else if(level == 3 ){
        int type = rand() % level + 1;
        p = Plane_Create(x,y,197,134,10,4,type + 1);
        p->hp = 3;
    } else if(level == 4){
        ///Boss
        SDL_Surface *sur = Resource_GetSurface(16);
        p = Plane_Create((WindowX - sur->w) / 2,0,sur->w,sur->h,0,0,16);
        p->hp = BossHp;
        p->alive = 0;
    }
    return p;
}

void Enemy_Move(Plane *enemy){
    if(!enemy->alive){
        enemy->rect.x = rand() % (WindowX - 197);
        enemy->rect.y = - rand() % 6000;
        enemy->alive = 1;
        enemy->hp = enemy->type - 1;
        return;
    }

    switch (enemy->type - 1) {
        case 1:
            enemy->rect.y += enemy->speedY;
            break;
        case 2:
            enemy->rect.y += enemy->speedY * 2;
            break;
        case 3:
            enemy->rect.x += enemy->speedX;
            enemy->rect.y += enemy->speedY;
            if(enemy->rect.x <= 0 && enemy->speedX < 0 || enemy->rect.x >= WindowX - enemy->rect.w && enemy->speedX > 0){
                enemy->speedX *= -1;
            }
            break;
    }
    if(enemy->rect.y > WindowY){
        enemy->alive = 0;
    }
}
