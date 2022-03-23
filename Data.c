//
// Created by lenovo on 2022/1/22.
//

#include "Data.h"

FontConfig *Text_Create(char *file,char *text ,int x,int y,int w,int h,SDL_Renderer *renderer ){
    FontConfig *font = malloc(sizeof(FontConfig));
    font->Color.a = 255;
    font->Color.r = 255;
    font->Color.g = 255;
    font->Color.b = 255;

    font->FontFile = TTF_OpenFont(file, FontSize);
    font->Surface = TTF_RenderUTF8_Blended(font->FontFile, text, font->Color);
    font->Texture = SDL_CreateTextureFromSurface(renderer,font->Surface);
    font->Rect.x = x;
    font->Rect.y = y;
    font->Rect.w = w;
    font->Rect.h = h;
    return font;
}

void Text_Draw(SDL_Renderer *renderer,FontConfig *font){
    if(font != NULL){
        SDL_RenderCopy(renderer,font->Texture,NULL,&font->Rect);
    }
}

void Text_Destroy(FontConfig *font){
    free(font);
}
