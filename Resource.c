//
// Created by lenovo on 2022/1/18.
//
#include "Resource.h"

#define PlayerImg "image\\Player.png"
#define GameBackGroundImg "image\\GameBackGround1.png"
#define BossImg "image\\Boss.png"

SDL_Texture *PlayerTexture = NULL;
SDL_Texture *GameBackGroundTexture = NULL;
SDL_Texture *EnemyTexture[3]  = {NULL, NULL, NULL};
SDL_Texture *BulletsTexture[7] = {NULL, NULL,NULL,NULL,NULL,NULL,NULL};
SDL_Surface *PlayerSurface = NULL;
SDL_Surface *GameBackGroundSurface = NULL;
SDL_Surface *EnemySurface[3] = {NULL,NULL,NULL};
SDL_Surface *BulletsSurface[7] = {NULL, NULL,NULL,NULL,NULL,NULL,NULL};
SDL_Surface *PropsSurface[4] = {NULL, NULL,NULL,NULL};
SDL_Texture *PropsTexture[4] = {NULL, NULL, NULL,NULL};
SDL_Texture *BossTexture = NULL;
SDL_Surface *BossSurface = NULL;
SDL_Surface *StartBackgroundSurface = NULL;
SDL_Texture *StartBackgroundTexture = NULL;
SDL_Texture *HelpTexture = NULL;
SDL_Surface *HelpSurface = NULL;


int Resource_Load(SDL_Renderer *renderer){
    PlayerTexture = IMG_LoadTexture(renderer,PlayerImg);
    GameBackGroundTexture = IMG_LoadTexture(renderer, GameBackGroundImg);
    StartBackgroundTexture = IMG_LoadTexture(renderer,"image\\StartBackground.png");
    EnemyTexture[0] = IMG_LoadTexture(renderer,"image\\Enemy1.png");
    EnemyTexture[1] = IMG_LoadTexture(renderer,"image\\Enemy2.png");
    EnemyTexture[2] = IMG_LoadTexture(renderer,"image\\Enemy3.png");
    BulletsTexture[0] = IMG_LoadTexture(renderer,"image\\Bullet1.png");
    BulletsTexture[1] = IMG_LoadTexture(renderer,"image\\Bullet2.png");
    BulletsTexture[2] = IMG_LoadTexture(renderer,"image\\Bullet3.png");
    BulletsTexture[3] = IMG_LoadTexture(renderer,"image\\Bullet4.png");
    BulletsTexture[4] = IMG_LoadTexture(renderer,"image\\Bullet5.png");
    BulletsTexture[5] = IMG_LoadTexture(renderer,"image\\Bullet6.png");
    BulletsTexture[6] = IMG_LoadTexture(renderer,"image\\Bullet7.png");
    PropsTexture[0] = IMG_LoadTexture(renderer,"image\\Prop1.png");
    PropsTexture[1] = IMG_LoadTexture(renderer,"image\\Prop2.png");
    PropsTexture[2] = IMG_LoadTexture(renderer,"image\\Prop3.png");
    PropsTexture[3] = IMG_LoadTexture(renderer,"image\\Prop4.png");
    BossTexture = IMG_LoadTexture(renderer,BossImg);
    HelpTexture = IMG_LoadTexture(renderer,"image\\Help.png");


    PlayerSurface = IMG_Load(PlayerImg);
    GameBackGroundSurface = IMG_Load(GameBackGroundImg);
    StartBackgroundSurface = IMG_Load("image\\StartBackGround.png");
    EnemySurface[0] = IMG_Load("image\\Enemy1.png");
    EnemySurface[1] = IMG_Load("image\\Enemy2.png");
    EnemySurface[2] = IMG_Load("image\\Enemy3.png");
    BulletsSurface[0] = IMG_Load("image\\Bullet1.png");
    BulletsSurface[1] = IMG_Load("image\\Bullet2.png");
    BulletsSurface[2] = IMG_Load("image\\Bullet3.png");
    BulletsSurface[3] = IMG_Load("image\\Bullet4.png");
    BulletsSurface[4] = IMG_Load("image\\Bullet5.png");
    BulletsSurface[5] = IMG_Load("image\\Bullet6.png");
    BulletsSurface[6] = IMG_Load("image\\Bullet7.png");
    PropsSurface[0] = IMG_Load("image\\Prop1.png");
    PropsSurface[1] = IMG_Load("image\\Prop2.png");
    PropsSurface[2] = IMG_Load("image\\Prop3.png");
    PropsSurface[3] = IMG_Load("image\\Prop4.png");
    BossSurface = IMG_Load(BossImg);
    HelpSurface = IMG_Load("image\\Help.png");


    if (PlayerTexture == NULL || GameBackGroundTexture == NULL) {
        SDL_Log("Can not load texture, %s", IMG_GetError());
        return 1;
    }
    return 0;
}

SDL_Surface *Resource_GetSurface(int type){
    switch (type){
        case 0:
            return PlayerSurface;
        case 1:
            return GameBackGroundSurface;
        case 2:
        case 3:
        case 4:
            return EnemySurface[type - 2];
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            return BulletsSurface[type - 5];
        case 12:
        case 13:
        case 14:
        case 15:
            return PropsSurface[type - 12];
        case 16:
            return BossSurface;
        case 17:
            return StartBackgroundSurface;
        case 18:
            return HelpSurface;
        default:
            SDL_Log("Can not load surface, %s", IMG_GetError());
            break;
    }
}

SDL_Texture *Resource_GetTexture( int type) {
    switch (type) {
        case 0:
            return PlayerTexture;
        case 1:
            return GameBackGroundTexture;
        case 2:
        case 3:
        case 4:
            return EnemyTexture[type - 2];
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            return BulletsTexture[type - 5];
        case 12:
        case 13:
        case 14:
        case 15:
            return PropsTexture[type - 12];
        case 16:
            return BossTexture;
        case 17:
            return StartBackgroundTexture;
        case 19:
            return HelpTexture;
        default:
            SDL_Log("Can not load texture, %s", IMG_GetError());
            break;
    }
}
void Resource_Unload(){
    SDL_FreeSurface(PlayerSurface);
    SDL_FreeSurface(GameBackGroundSurface);
    for (int i = 0; i < 3; ++i) {
        SDL_FreeSurface(EnemySurface[i]);
    }
    for (int i = 0; i < 7; ++i) {
        SDL_FreeSurface(BulletsSurface[i]);
    }
    for (int i = 0; i < 4; ++i) {
        SDL_FreeSurface(PropsSurface[i]);
    }
    SDL_FreeSurface(BossSurface);
    SDL_FreeSurface(StartBackgroundSurface);

    SDL_DestroyTexture(PlayerTexture);
    SDL_DestroyTexture(GameBackGroundTexture);
    SDL_DestroyTexture(StartBackgroundTexture);
    for (int i = 0; i < 3; ++i) {
        SDL_DestroyTexture(EnemyTexture[i]);
    }
    for (int i = 0; i < 7; ++i) {
        SDL_DestroyTexture(BulletsTexture[i]);
    }
    for (int i = 0; i < 4; ++i) {
        SDL_DestroyTexture(PropsTexture[i]);
    }
    SDL_DestroyTexture(BossTexture);
}