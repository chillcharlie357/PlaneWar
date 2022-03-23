//
// Created by lenovo on 2022/1/22.
//

#include "Props.h"


Prop *Prop_Create(int x, int y,int w,int h,int type,int exist){
    Prop *p = malloc(sizeof(Prop));
    p->Rect.x = x;
    p->Rect.y = y;
    p->Rect.w = w;
    p->Rect.h = h;
    p->type = type;
    p->exist = exist;
    p->speed = 5;
    return p;
}
void Prop_Draw(SDL_Renderer *renderer,Prop *self){
    if(self->exist) {
        SDL_RenderCopy(renderer, Resource_GetTexture(self->type),NULL,&self->Rect);
    }
}
void Prop_Move(Prop *self){
    if(self->exist) {
        self->Rect.y += self->speed;
    }
    if(self->Rect.y > WindowY){
        self->exist = 0;
    }
}
int Prop_Load(Prop *self,int x,int y){
    if(!self->exist) {
        self->exist = 1;
        self->Rect.x = x;
        self->Rect.y = y;
        return 1;
    }
    return 0;
}
void Prop_Work(Prop *self,Plane *p){
    switch(self->type - 12){
        case 0:
            p->hp += 10;
            if(p->hp > PlayerHp){
                p->hp = PlayerHp;
            }
            break;
        case 1:
            p->bullet_damage_increase = 1;
            break;
        case 2:
            p->have_shield = 1;
            break;
        case 3:
            p->special_attack = 1;
            break;
        default:
            SDL_Log("Unknown Type of Prop");
    }
    self->exist = 0;
}
void Prop_Destroy(Prop* self){
    free(self);
}
