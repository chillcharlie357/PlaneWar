//
// Created by lenovo on 2022/1/19.
//

#include "PlayerControl.h"

void Player_Operation(SDL_Event *event,Plane *Player){
    int speedX = Player->speedX;
    int speedY = Player->speedY;
    switch (event->key.keysym.sym) {
        case SDLK_a:
            if(Player->rect.x > 0 ){
                Player->rect.x -=  speedX;
            }
            break;
        case SDLK_d:
            if(Player->rect.x < WindowX - Player->rect.w ){
                Player->rect.x += speedX;
            }
            break;
        case SDLK_w:
            if(Player->rect.y > 0){
                Player->rect.y -= speedY;
            }
            break;
        case SDLK_s:
            if(Player->rect.y < WindowY - Player->rect.h){
                Player->rect.y += speedY;
            }
            break;
    }
}


