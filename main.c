#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "utilities.h"
#include "animation.h"
#include "player.h"
#include "object.h"



//SCREEN
extern const int height;
extern const int width;

//RIN CHARACTER
extern const int rin_frameWidth;
extern const int rin_frameHeight;
extern const int rin_textureWidth;
extern const int rin_textureHeight;
extern const int rin_characterWidth;
extern const int rin_characterHeight;

//RIVER BACKGROUND1
extern const int river_frameWidth;
extern const int river_frameHeight;
extern const int river_textureHeight;
extern const int river_textureWidth;
extern const int river_Height;
extern const int river_Width;


bool initializedSucces = true;

int main(int argc, char* argv[]) {
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

    SDL_Window *window = SDL_CreateWindow("Naruto: Rin Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;


    SDL_Texture *background = LoadTexture("images/background1/background.png",renderer);
    if(background == NULL ) {
        printf("Unable to load Texture\n");
        initializedSucces = false;
    }

    PPlayer player1 = player_create();
    player_setTextureWidth(player1,rin_textureWidth);
    player_setTextureHeight(player1,rin_textureHeight);
    player_setPlayerRectW(player1,rin_frameWidth);
    player_setPlayerRectH(player1,rin_frameWidth);
    player_setPlayerPositionW(player1,rin_characterWidth);
    player_setPlayerPositionH(player1,rin_characterHeight);
    player_setMoveSpeed(player1,300.0f);
    player_setPlayerPositionX(player1,0);
    player_setPlayerPositionY(player1,405);
    player_setTexturePath(player1,renderer,"images/rin/rin_nohararight.png");

    PObject river = object_create();
    object_setTextureWidth(river,river_textureWidth);
    object_setTextureHeight(river,river_textureHeight);
    object_setObjectRectW(river,river_frameWidth);
    object_setObjectRectH(river,river_frameHeight);
    object_setObjectPositionW(river,river_Width);
    object_setObjectPositionH(river,river_Height);
    object_setObjectPositionX(river,0);
    object_setObjectPositionY(river,800);
    object_setTexturePath(river,renderer,"images/background1/river.png");


    bool running = true;

    while(running && initializedSucces == true) {
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
                     if(player_getDead(player1)==false) {

                     }
                        break;
                case SDLK_u:
                    player_setHealth(player1,player_getHealth(player1)-10);
                    break;
                }
            } else if(event.type == SDL_MOUSEMOTION) {
                printf("X: %d | Y: %d\n",event.motion.x, event.motion.y);
            }
        }
        if(state[SDL_SCANCODE_D]) {
            if(player_getDead(player1)==false) {
                int currentX = player_getPlayerPositionX(player1) + (player_getMoveSpeed(player1) * deltaTime);
                player_setPlayerPositionX(player1,currentX);
                player_setCurDoing(player1,1);
                player_setLeft(player1,false);
            }
        } else if(state[SDL_SCANCODE_A]) {
            if(player_getDead(player1)==false) {
                int currentX = player_getPlayerPositionX(player1) - (player_getMoveSpeed(player1) * deltaTime);
                player_setPlayerPositionX(player1,currentX);
                player_setCurDoing(player1,0);
                player_setLeft(player1,true);
            }
        } else if(!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) {
             if(player_getDead(player1)==false) {
                    if(player_getLeft(player1)==true) {
                       player_setCurDoing(player1,2);
                    } else if(player_getLeft(player1) == false) {
                        player_setCurDoing(player1,3);
                    }
            }
        } else if(!state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D] && state[SDL_SCANCODE_LSHIFT]) {
            if(player_getDead(player1)==false) {
                int currentX = player_getPlayerPositionX(player1) + (player_getMoveSpeed(player1)+150 * deltaTime);
                player_setPlayerPositionX(player1,currentX);
                player_setCurDoing(player1,5);
                player_setLeft(player1,false);
                printf("YAY");
            }
        }
        if(player_getHealth(player1)==0) {
            if(player_getPlayerPositionY(player1)==1800) {
                player_setFrameTime(player1,0);
            }
            player_setCurDoing(player1,4);
        } else {
           // printf("%d\n",player_getHealth(player1));
        }
        //engine_gravity();
        object_setFrameTime(river,object_getFrameTime(river)+deltaTime);
        player_setFrameTime(player1, player_getFrameTime(player1)+deltaTime);
        switch(player_getCurDoing(player1)) {
            case 0: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,6200,6700,0.15f,rin_frameHeight); break;
            case 1: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,6200,6700,0.15f,rin_frameHeight); break;
            case 2: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,5200,5700,0.25f,rin_frameHeight); break;
            case 3: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,5200,5700,0.25f,rin_frameHeight); break;
            case 4: if(player_getDead(player1)==false || player_getPlayerRectY(player1) != 1800) { animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),4,1400,1800,0.1f,rin_frameHeight); } player_setDead(player1,true); break;
            case 5: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,3000,3500,0.25f,rin_frameHeight); break;
        }
        animation_create(object_getPFrameTime(river),object_getObjectRectPY(river),object_getObjectRectPX(river),3,-111,222,0.5f,river_frameHeight);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
        animation_show(renderer,player1,player_getLeft(player1));
        animation_show(renderer,river,object_getLeft(river));
        SDL_RenderPresent(renderer);
    }
    player_playerRemove(player1);
    player1 = NULL;

    object_objectRemove(river);
    river = NULL;

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(background);
    SDL_DestroyWindow(window);

    background = NULL;
    renderer = NULL;
    window = NULL;

    SDL_Quit();
    return 0;
}
