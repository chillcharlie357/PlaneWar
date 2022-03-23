#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <math.h>
#include "Plane.h"
#include "Config.h"
#include "Resource.h"
#include "PlayerControl.h"
#include "EnemyControl.h"
#include "BulletsControl.h"
#include "CheckCollision.h"
#include "Data.h"
#include "Props.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

Plane *Player = NULL;
Plane *Enemy[EnemyCount];
Plane *Boss = NULL;
Bullet *PlayerBullets[PlayerBulletsCount];
Bullet *EnemyBullets[EnemyBulletsCount];
Bullet *BossBullets[BossBulletsCount];
Bullet *BossLaser = NULL;
FontConfig *ScoreFont = NULL;
FontConfig *PlayerHealth = NULL;
FontConfig *PromptFont = NULL;
FontConfig *LevelFont = NULL;
FontConfig *BossHealth = NULL;
Prop *Props[PropCount];

int level = 0;
int score = 0;
long Prop_StartTime[2] = {0};
long Prop_CurTime[2] = {0};
long Laser_StartTime = 0;
long Laser_CurTime = 0;
int CurHp = 0;
int IsWin = 0;


void Draw();
void GameLoop();
void Quit();
void CreateEnemy();
void MoveEnemy();
void DrawEnemy();
void CreateBullets();
void MoveBullets();
void DrawBullets();
void LoadBullets();
int IsAlive();
void StatusBoard();
void NextLevel();
void CreateProps();
void DrawProps();
void MoveProps();
void LoadProps();
void CheckProps();
void Prompt();
void Helper();

int SDL_main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("PlaneWar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowX, WindowY, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Resource_Load(renderer);

    GameStart:
    level = 1;

    Player = Plane_Create(WindowX / 2 - 50,WindowY - 66,100,66,40,40,0);
    Player->hp = PlayerHp;
    Boss = Enemy_Create(4);
    Boss->alive = 0;

    CreateBullets();
    CreateEnemy();
    CreateProps();
    SDL_Event *MainEvent;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Resource_GetTexture(17),NULL,NULL);
    SDL_RenderPresent(renderer);
    while(SDL_WaitEvent(MainEvent)){
        int x,y;
        switch (MainEvent->type) {
            case SDL_MOUSEBUTTONDOWN:
                x = MainEvent->button.x;
                y = MainEvent->button.y;
//                SDL_Log("(%d,%d)",x,y);
                if(x > 228 && x < 457 && y > 393 && y < 438){
                    GameLoop();
                    SDL_Delay(1000);
                    Prompt();
                }
                if(x > 230 && x < 460 && y > 520 && y < 567){
                    Helper();
                }
                break;
            case SDL_KEYDOWN:
                switch(MainEvent->key.keysym.sym) {
                    case SDLK_r:
                        level = 1;
                        score = 0;
                        goto GameStart;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                Quit();
                break;
            default:
                break;
        }
    }
    return 0;
}

void Helper(){
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, Resource_GetTexture(17),NULL,NULL);
                    SDL_RenderPresent(renderer);
                    return;
                }
                break;
            case SDL_QUIT:
                Quit();
                break;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, Resource_GetTexture(19),NULL,NULL);
        SDL_RenderPresent(renderer);
    }
}

void Quit(){
    Resource_Unload();
    for (int i = 0; i < EnemyCount; ++i) {
        Plane_Destroy(Enemy[i]);
    }
    for (int i = 0; i < PlayerBulletsCount; ++i) {
        Bullet_Destroy(PlayerBullets[i]);
    }
    for (int i = 0; i < EnemyBulletsCount; ++i) {
        Bullet_Destroy(EnemyBullets[i]);
    }
    for (int i = 0; i < PropCount; ++i) {
        Prop_Destroy(Props[i]);
    }
    Text_Destroy(ScoreFont);
    Text_Destroy(PlayerHealth);
    Plane_Destroy(Player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Draw(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Resource_GetTexture(1),NULL,NULL);
    Plane_Draw(Player,renderer);
    Plane_Draw(Boss,renderer);
    DrawEnemy();
    DrawBullets();
    DrawProps();
    Text_Draw(renderer,ScoreFont);
    Text_Draw(renderer,PlayerHealth);
    Text_Draw(renderer,LevelFont);
    if(Boss->alive){
        Text_Draw(renderer,BossHealth);
    }
    SDL_RenderPresent(renderer);
}

void CreateEnemy(){
    int cnt = 0;
    for (int i = 0; i < EnemyCount; ++i) {
        Enemy[i] = Enemy_Create(level);
        SDL_Surface *sur = Resource_GetSurface(Enemy[i]->type + 5);
        for (int j = 0; j < EnemyBulletsCount / EnemyCount; ++j) {
            EnemyBullets[cnt] = Bullet_Create(Enemy[i]->rect.x + Enemy[i]->rect.w / 2,Enemy[i]->rect.y,sur->w,sur->h,0,10,0,Enemy[i]->type + 5);
            cnt++;
        }
    }
    SDL_Surface *sur = Resource_GetSurface(9);
    for (int i = 0; i < BossBulletsCount / 2; ++i) {
        BossBullets[i] = Bullet_Create(Boss->rect.x + sur->w / 2,Boss->rect.y,sur->w,sur->h,(rand() % 10 ) * pow(-1.0,rand() % 2 * 1.0),rand() % 3,0,9);
    }
    for (int i = BossBulletsCount / 2; i < BossBulletsCount; ++i) {
        BossBullets[i] = Bullet_Create(Boss->rect.x + sur->w / 2,Boss->rect.y,sur->w,sur->h,(rand() % 5 ) * pow(-1.0,rand() % 2 * 1.0),5,0,10);
    }
    SDL_Surface *s = Resource_GetSurface(11);
    BossLaser = Bullet_Create(Boss->rect.x + s->w / 2,Boss->rect.y,s->w,s->h,0,0,0,11);
}
void MoveEnemy(){
        for (int i = 0; i < EnemyCount; ++i) {
            Enemy_Move(Enemy[i]);
            if(Collision_Check(Enemy[i]->rect,Player->rect) && Enemy[i]->alive){
                Player->hp -= 1;
                Enemy[i]->hp -= 10;
            }
            if(Enemy[i]->rect.y > WindowY - Enemy[i]->rect.h && Enemy[i]->alive){
                Player->hp -= 1;
                Enemy[i]->alive = 0;
            }
            IsAlive();
        }
}
void DrawEnemy(){
    for (int i = 0; i < EnemyCount; ++i) {
        Plane_Draw(Enemy[i],renderer);
    }
}

int IsAlive(){
    for (int i = 0; i < EnemyCount; ++i) {
        if(Enemy[i]->hp <= 0){
            Enemy[i]->alive = 0;
        }
    }
    if(Player->hp <= 0){
        Player->alive = 0;
        return -1;
    }
    if(Boss->hp <= 0){
        Boss->alive = 0;
        return 1;
    }
    return 0;
}

void CreateBullets(){
    SDL_Surface *sur = Resource_GetSurface(5);
    for (int i = 0; i < PlayerBulletsCount; ++i){
        PlayerBullets[i] = Bullet_Create(Player->rect.x + Player->rect.w / 2,Player->rect.y,sur->w,sur->h,0,-20,0,5);
    }

}
void MoveBullets(){
    for (int i = 0; i < PlayerBulletsCount; ++i) {
        if (PlayerBullets[i] != NULL){
            for (int j = 0; j < EnemyCount; ++j) {
                ///Enemy PlayerBullets
                if(PlayerBullets[i]->exist && Enemy[j]->alive && Collision_Check(PlayerBullets[i]->rect,Enemy[j]->rect)){
                    Enemy[j]->hp -= PlayerBullets[i]->damage;
                    PlayerBullets[i]->exist = 0;
                    IsAlive();
                    if(Enemy[j]->hp <= 0){
                        score += 1;
                    }
                }
                ///Boss PlayerBullets
                if(Boss->alive){
                    if(PlayerBullets[i]->exist  && Collision_Check(PlayerBullets[i]->rect,Boss->rect)){
                        Boss->hp -= PlayerBullets[i]->damage;
                        PlayerBullets[i]->exist = 0;
                        IsAlive();
                    }
                }
            }
            Bullet_Move(PlayerBullets[i]);
        }
    }
    ///Player EnemyBullets
    const int n = EnemyBulletsCount / EnemyCount;
    for (int i = 0; i < EnemyCount; ++i) {
        if(Enemy[i]->alive){
            for (int j = i * n; j < (i + 1) * n; ++j) {
                Bullet_Load(Enemy[i]->rect.x + Enemy[i]->rect.w / 2, Enemy[i]->rect.y, EnemyBullets[j]);
                Bullet_Move(EnemyBullets[j]);
                if(EnemyBullets[j]->exist && Collision_Check(EnemyBullets[j]->rect,Player->rect)){
                    Player->hp -= EnemyBullets[j]->damage;
                    EnemyBullets[j]->exist = 0;
                    IsAlive();
                }
            }
        }
    }
    ///BossBullets Player
    if(Boss->alive){
        for (int i = 0; i < BossBulletsCount; ++i) {
            Bullet_Load(Boss->rect.x + Boss->rect.w / 2 ,Boss->rect.y + Boss->rect.h,BossBullets[i]);
            Bullet_Move(BossBullets[i]);
            if(BossBullets[i]->exist && Collision_Check(BossBullets[i]->rect,Player->rect)){
                Player->hp -= BossBullets[i]->damage;
                BossBullets[i]->exist = 0;
                IsAlive();
            }
        }
    }
    ///Boss Laser
    if(Boss->alive && Boss->hp < BossHp / 2){
        if(!BossLaser->exist){
            Laser_StartTime = SDL_GetTicks();
        }
        SDL_Surface *s = Resource_GetSurface(11);
        Bullet_Load(rand() % (WindowX - s->w),Boss->rect.y + Boss->rect.h,BossLaser);
        if(BossLaser->exist && Collision_Check(BossLaser->rect,Player->rect)){
            Player->hp -= BossLaser->damage;
            BossLaser->exist = 0;
            Laser_StartTime = 0;
            Laser_CurTime = 0;
            IsAlive();
        }
        Laser_CurTime = SDL_GetTicks();
        if(Laser_CurTime - Laser_StartTime >= BossLaserLastTime){
            BossLaser->exist = 0;
            Laser_StartTime = 0;
            Laser_CurTime = 0;
        }
    }
}
void DrawBullets(){
    for (int i = 0; i < PlayerBulletsCount; ++i) {
        if (PlayerBullets[i] != NULL){
            Bullet_Draw(PlayerBullets[i],renderer);
        }
    }
    for (int i = 0; i < EnemyBulletsCount; ++i) {
        if(EnemyBullets[i] != NULL){
            Bullet_Draw(EnemyBullets[i],renderer);
        }
    }
    for (int i = 0; i < BossBulletsCount; ++i) {
        Bullet_Draw(BossBullets[i],renderer);
    }
    Bullet_Draw(BossLaser,renderer);
}

void LoadBullets(){
    for (int i = 0; i < PlayerBulletsCount; ++i) {
        if(PlayerBullets[i] != NULL){
            if(Player->bullet_damage_increase){
                PlayerBullets[i]->damage += 1;
                Player->bullet_damage_increase = 0;
            }
            SDL_Surface *sur = Resource_GetSurface(PlayerBullets[i]->type);
            Bullet_Load(Player->rect.x + (Player->rect.w - sur->w) / 2, Player->rect.y, PlayerBullets[i]);
            break;
        }
    }
}

void StatusBoard(){
    char s[50] = {0};
    char target1[50] = "Score:";
    itoa(score,s,10);
    strcat(target1,s);
    ScoreFont = Text_Create("ALGER.TTF",target1,WindowX - 200, 0 ,200,100,renderer);
    if(!Player->have_shield){
        char HP[50] = {0};
        char target2[50] = "HP:";
        itoa(Player->hp,HP,10);
        strcat(target2,HP);
        PlayerHealth = Text_Create("ALGER.TTF",target2,WindowX -200,100,200,100,renderer);
    }
    char target3[50] = "Level:";
    char NowLevel[50] = {0};
    itoa(level,NowLevel,10);
    strcat(target3,NowLevel);
    LevelFont = Text_Create("ALGER.TTF",target3,WindowX / 2 - 50,0,100,50,renderer);
    if (Boss->alive){
        char target4[50] = "BossHp:";
        char Hp[50] = {0};
        itoa(Boss->hp,Hp,10);
        strcat(target4,Hp);
        BossHealth = Text_Create("ALGER.TTF",target4,WindowX / 2 - 50,52,100,50,renderer);
    }

}

void CreateProps(){
    for (int i = 0; i < PropCount; ++i) {
        SDL_Surface *sur = Resource_GetSurface(i % 4 + 12);
        Props[i] = Prop_Create(0,0,sur->w,sur->h,i % 4 + 12,0);
    }
}
void DrawProps(){
    for (int i = 0; i < PropCount; ++i) {
        Prop_Draw(renderer,Props[i]);
    }
}
void MoveProps(){
    for (int i = 0; i < PropCount; ++i) {
        if(Props[i]->exist){
            Prop_Move(Props[i]);
            if(Collision_Check(Props[i]->Rect,Player->rect)){
                Prop_Work(Props[i],Player);
            }
        }
    }
}
void LoadProps(){
    for (int i = 0; i < EnemyCount; ++i) {
        if(!Enemy[i]->alive){
            ///random props
            int create = rand() % 100;
            if(create <= PropRate){
                while (1){
                    int result = rand() % PropCount;
                    if(Prop_Load(Props[result],Enemy[i]->rect.x,Enemy[i]->rect.y)){
                        break;
                    }
                }
            }
        }
    }
}
void CheckProps(){
    for (int i = 0; i < PropCount; ++i) {
        if(Player->have_shield && Prop_StartTime[0] == 0){
            Prop_StartTime[0] = SDL_GetTicks();
            CurHp = Player->hp;
            Player->hp = 999999;
        }
        if(Player->special_attack && Prop_StartTime[1] == 0){
            Prop_StartTime[1] = SDL_GetTicks();
            SDL_Surface *sur = Resource_GetSurface(6);
            for (int j = 0; j < PlayerBulletsCount; ++j) {
                PlayerBullets[j]->type += 1;
                PlayerBullets[j]->damage += 2;
                PlayerBullets[j]->rect.w = sur->w;
                PlayerBullets[j]->rect.h = sur->h;
            }
        }

        if(Prop_StartTime[0] != 0){
            Prop_CurTime[0] = SDL_GetTicks();
            if(Prop_CurTime[0] - Prop_StartTime[0] >= PropLastTime){
                Prop_StartTime[0] = 0;
                Player->have_shield = 0;
                Player->hp = CurHp;
            }
        }
        if(Prop_StartTime[1] != 0){
            Prop_CurTime[1] = SDL_GetTicks();
            if(Prop_CurTime[1] - Prop_StartTime[1] >= 4 * PropLastTime){
                Prop_StartTime[1] = 0;
                Player->special_attack = 0;
                SDL_Surface *sur = Resource_GetSurface(5);
                for (int j = 0; j < PlayerBulletsCount; ++j) {
                    PlayerBullets[j]->type -= 1;
                    PlayerBullets[j]->damage -= 2;
                    PlayerBullets[j]->rect.w = sur->w;
                    PlayerBullets[j]->rect.h = sur->h;
                }
            }
        }
    }
}



void NextLevel(){
    if(score >= Level_1 && level == 1){
        level = 2;
        CreateEnemy();
    }
    if(score >= Level_2 && level == 2){
        level = 3;
        CreateEnemy();
    }
    if(score >= Level_3 && level == 3){
        level = 4;
        Boss->alive = 1;
        for (int i = 0; i < EnemyCount; ++i) {
            Enemy[i]->alive = 0;
        }
        for (int i = 0; i < EnemyBulletsCount; ++i) {
            EnemyBullets[i]->exist = 0;
        }
    }
}

void Prompt(){
    char value[20] = {0};
    if(IsWin){
        strcpy(value, "Win!");
    } else {
        strcpy(value, "Lose!R to replay!");
    }
    int w = 70 * strlen(value);
    if(w > WindowX){
        w = WindowX;
    }
    PromptFont = Text_Create("ALGER.TTF",value,WindowX / 2 - w / 2, WindowY / 2 - 50,w,100,renderer);
    SDL_RenderClear(renderer);
    Text_Draw(renderer,PromptFont);
    SDL_RenderPresent(renderer);
}

void GameLoop(){
    int quit = 0;
    while(!quit){
        long begin = SDL_GetTicks();
        StatusBoard();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    Quit();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("(%d,%d)\n",event.button.x,event.button.y);
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE){
                        LoadBullets();
                    } else {
                        Player_Operation(&event,Player);
                    }
                    break;
            }
        }
        if(level != 4){
            MoveEnemy();
        }
        MoveBullets();
        MoveProps();
        if(level != 4){
            LoadProps();
        }
        CheckProps();

        if(IsAlive() < 0){
            quit = 1;
//            SDL_Log("Default");
        } else if(IsAlive() > 0){
//            SDL_Log("Win");
            quit = 1;
            IsWin = 1;
        }

        NextLevel();
        Draw();
        long current = SDL_GetTicks();
        long cost = current - begin;
        long frame = 1000 / FRAMERATE;
        long delay = frame - cost;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}
