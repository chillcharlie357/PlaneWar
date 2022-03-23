//
// Created by lenovo on 2022/1/19.
//

#ifndef PROJECT_2_ENEMYCONTROL_H
#define PROJECT_2_ENEMYCONTROL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Plane.h"
#include "Config.h"
#include "BulletsControl.h"
#include "Resource.h"

Plane *Enemy_Create(int level);
void Enemy_Move(Plane *enemy);

#endif //PROJECT_2_ENEMYCONTROL_H
