//
// Created by lenovo on 2022/1/22.
//

#ifndef PROJECT_2_PROPS_H
#define PROJECT_2_PROPS_H

#include "Resource.h"
#include "Plane.h"

typedef struct {
    SDL_Rect Rect;
    int type;
    int exist;
    int speed;
} Prop;


Prop *Prop_Create(int x, int y,int w,int h,int type,int exist);
void Prop_Draw(SDL_Renderer *renderer,Prop *self);
void Prop_Move(Prop *self);
int Prop_Load(Prop *self,int x,int y);
void Prop_Work(Prop *self,Plane *p);
void Prop_Destroy(Prop* self);

#endif //PROJECT_2_PROPS_H
