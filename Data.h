//
// Created by lenovo on 2022/1/22.
//

#ifndef PROJECT_2_DATA_H
#define PROJECT_2_DATA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Config.h"
#include "Resource.h"
#include <string.h>

typedef struct {
    TTF_Font *FontFile;
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect Rect;
    SDL_Color Color;
} FontConfig;

FontConfig *Text_Create(char *file,char *text ,int x,int y,int w,int h,SDL_Renderer *renderer);
void Text_Draw(SDL_Renderer *renderer,FontConfig *font);
void Text_Destroy(FontConfig *font);

#endif //PROJECT_2_DATA_H
