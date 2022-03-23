//
// Created by lenovo on 2022/1/19.
//

#ifndef PROJECT_2_PLAYERCONTROL_H
#define PROJECT_2_PLAYERCONTROL_H

#include <SDL2/SDL.h>
#include "Plane.h"
#include "Config.h"


///Move,Attack,Use game props
void Player_Operation(SDL_Event *event,Plane *Player);

#endif //PROJECT_2_PLAYERCONTROL_H
