#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utilities.h"
#include "animation.h"
#include "player.h"

#include "SDL.h"
#include "SDL_image.h"

extern const int height;
extern const int width;

extern const int frameWidth;
extern const int frameHeight;

extern const int frameHeightRiver;
extern const int frameWidthRiver;

bool initializedSucces = true;

int main(int argc, char* argv[]) {
    int textureWidth = 100;
    int textureHeight = 2200;
    int characterWidth = 100;
    int characterHeight = 100;

    int riverHeight = 333;
    int riverWidth = 704;
    int riverSizeHeight = 300;
    int riverSizeWidth = 2000;


    //int curDoing = 4;

    bool left = false;

    float frameTime = 0;
    float frameTime2 = 0;
    int prevTime = 0;
    int currentTime = 0;
    float deltaTime = 0;

    if(SDL_Init(SDL_INIT_VIDEO)!=0) {
        printf("Unable to initialize SDL: %s\n",SDL_GetError());
        initializedSucces = false;
    }
    int imgFlag = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(imgFlag) & imgFlag)) {
        printf("Unable to initialize SDL Image: %s\n",IMG_GetError());
        initializedSucces = false;
    }

    SDL_Window *window = SDL_CreateWindow("Naruto: Rin Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;


    SDL_Texture *background = LoadTexture("images/background1/background.png",renderer);
    if(background == NULL ) {
        printf("Unable to load Texture\n");
        initializedSucces = false;
    }

    PPlayer player1 = player_create();
    player_setTextureWidth(player1,textureWidth);
    player_setTextureHeight(player1,textureHeight);
    player_setPlayerRectW(player1,frameWidth);
    player_setPlayerRectH(player1,frameWidth);
    player_setPlayerPositionW(player1,characterWidth);
    player_setPlayerPositionH(player1,characterHeight);
    player_setMoveSpeed(player1,300.0f);
    player_setPlayerPositionX(player1,0);
    player_setPlayerPositionY(player1,405);
    player_setTexturePath(player1,renderer,"images/rin/rin_nohara.png");

    PPlayer player2 = player_create();
    player_setTextureWidth(player2,riverWidth);
    player_setTextureHeight(player2,riverHeight);
    player_setPlayerRectW(player2,frameWidthRiver);
    player_setPlayerRectH(player2,frameHeightRiver);
    player_setPlayerPositionW(player2,riverSizeWidth);
    player_setPlayerPositionH(player2,riverSizeHeight);
    player_setPlayerPositionX(player2,0);
    player_setPlayerPositionY(player2,800);
    player_setTexturePath(player2,renderer,"images/background1/river.png");


    bool running = true;

    while(running && initializedSucces == true) {
        int currentX = 0;
        int currentY = 0;
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON_LEFT){

                } else if(event.button.button == SDL_BUTTON_RIGHT) {

                }
            } else if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                case SDLK_SPACE:
                        break;
                }
            } else if(event.type == SDL_MOUSEMOTION) {
               // printf("X: %d | Y: %d\n",event.motion.x, event.motion.y);
            }
        }
        if(state[SDL_SCANCODE_D]) {
            currentX = player_getPlayerPositionX(player1) + (player_getMoveSpeed(player1) * deltaTime);
            player_setPlayerPositionX(player1,currentX);
            player_setCurDoing(player1,1);
            left = false;
        } else if(state[SDL_SCANCODE_A]) {
            currentX = player_getPlayerPositionX(player1) - (player_getMoveSpeed(player1) * deltaTime);
            player_setPlayerPositionX(player1,currentX);
            player_setCurDoing(player1,0);
            left = true;
        } else if(!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) {
            if(left==true) {
               player_setCurDoing(player1,2);
            } else if(left == false) {
                player_setCurDoing(player1,3);
            }
        }

        //engine_gravity();

        frameTime = frameTime + deltaTime;
        frameTime2 = frameTime2 + deltaTime;
        switch(player_getCurDoing(player1)) {
        case 0: animation(&frameTime,player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),6,-100,500,0.15f,frameHeight); break;
        case 1: animation(&frameTime,player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),6,500,1100,0.15f,frameHeight); break;
        case 2: animation(&frameTime,player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,1100,1600,0.25f,frameHeight); break;
        case 3: animation(&frameTime,player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,1600,2100,0.25f,frameHeight); break;
        }

        animation(&frameTime2,player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),3,-111,222,0.5f,frameHeightRiver);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
        SDL_RenderCopy(renderer,player_getTexture(player1),player_getPlayerRect(player1),player_getPlayerPosition(player1));
        SDL_RenderCopy(renderer,player_getTexture(player2),player_getPlayerRect(player2),player_getPlayerPosition(player2));
        SDL_RenderPresent(renderer);
    }
    player_playerRemove(player1);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    renderer = NULL;
    window = NULL;

    SDL_Quit();
    return 0;
}
