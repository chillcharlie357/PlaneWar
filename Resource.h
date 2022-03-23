//
// Created by lenovo on 2022/1/18.
//

#ifndef PROJECT_2_RESOURCE_H
#define PROJECT_2_RESOURCE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Config.h"

int Resource_Load(SDL_Renderer *renderer);
SDL_Surface *Resource_GetSurface(int type);
SDL_Texture *Resource_GetTexture( int type);
void Resource_Unload();

#endif //PROJECT_2_RESOURCE_H
