#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "utilities.h"
#include "animation.h"
#include "player.h"
#include "engine.h"
#include "object.h"
#include "homescreen.h"


//SCREEN
extern const int height;
extern const int width;

//HOMSCREEN
extern const int heightHomeScreen;
extern const int widthHomeScreen;

extern const int logoHeight;
extern const int logoWidth;

extern const int textHeight;
extern const int textWidth;

extern const int startHeight;
extern const int startWidth;

extern const int exitHeight;
extern const int exitWidth;

extern const int settingsHeight;
extern const int settingsWidth;

//RIN CHARACTER
extern const int rin_frameWidth;
extern const int rin_frameHeight;
extern const int rin_textureWidth;
extern const int rin_textureHeight;
extern const int rin_characterWidth;
extern const int rin_characterHeight;
extern const float rin_jumpDelay;

//RIVER BACKGROUND1
extern const int river_frameWidth;
extern const int river_frameHeight;
extern const int river_textureHeight;
extern const int river_textureWidth;
extern const int river_Height;
extern const int river_Width;

//CLOUD BACKGROUND1
extern const int cloud_frameWidth;
extern const int cloud_frameHeight;
extern const int cloud_textureHeight;
extern const int cloud_textureWidth;
extern const int cloud_Height;
extern const int cloud_Width;


bool initializedSucces = true;

int main(int argc, char* argv[]) {

    if(SDL_Init(SDL_INIT_VIDEO)!=0) {

    printf("Unable to initialize SDL: %s\n",SDL_GetError());
        initializedSucces = false;
    }

    if(SDL_Init(SDL_INIT_GAMECONTROLLER)!= 0) {
         printf("Unable to initialize SDL: %s\n",SDL_GetError());
        initializedSucces = false;
    }
    int imgFlag = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(imgFlag) & imgFlag)) {
        printf("Unable to initialize SDL Image: %s\n",IMG_GetError());
        initializedSucces = false;
    }

    SDL_GameController *controller1 = NULL;
    if(SDL_NumJoysticks() < 1) {
        printf("No controller found!\n");
    } else {
        controller1 = SDL_GameControllerOpen(0);
        if(controller1 == NULL) {
            printf("Cannot connect with controller: SDL ERROR: %s",SDL_GetError());
        }
    }

    int prevTime = 0;
    int currentTime = 0;
    float deltaTime = 0;

    float homeScreenTime=0;

    bool homeScreenRunning = true;
    bool choosePlayerRunning = true;
    bool running = true;

    SDL_Window *homeScreenWindow= SDL_CreateWindow("Naruto: Rin Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, widthHomeScreen, heightHomeScreen,SDL_WINDOW_BORDERLESS);
    SDL_Renderer *homeScreenRenderer = SDL_CreateRenderer(homeScreenWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event homeScreenEvent;

    SDL_Texture *homeScreenBackground = LoadTexture("images/homeScreen/background.png",homeScreenRenderer);
    if(homeScreenBackground == NULL ) {
        printf("Unable to load Texture\n");
        initializedSucces = false;
        homeScreenRunning = false;
    }

    PObject logo = object_create();
    object_setTextureWidth(logo,logoWidth);
    object_setTextureHeight(logo,logoHeight);
    object_setObjectRectW(logo,logoWidth);
    object_setObjectRectH(logo,logoHeight);
    object_setObjectPositionW(logo,logoWidth);
    object_setObjectPositionH(logo,logoHeight);
    object_setObjectPositionX(logo,350);
    object_setObjectPositionY(logo,230);
    object_setTexturePath(logo,homeScreenRenderer,"images/homeScreen/logo.png");

    PObject text = object_create();
    object_setTextureWidth(text,textWidth);
    object_setTextureHeight(text,textHeight);
    object_setObjectRectW(text,textWidth);
    object_setObjectRectH(text,textHeight);
    object_setObjectPositionW(text,textWidth-100);
    object_setObjectPositionH(text,textHeight+50);
    object_setObjectPositionX(text,20);
    object_setObjectPositionY(text,70);
    object_setTexturePath(text,homeScreenRenderer,"images/homeScreen/text.png");


    PObject settings = object_create();
    object_setTextureWidth(settings,settingsWidth);
    object_setTextureHeight(settings,settingsHeight);
    object_setObjectRectW(settings,settingsWidth);
    object_setObjectRectH(settings,settingsHeight);
    object_setObjectPositionW(settings,settingsWidth);
    object_setObjectPositionH(settings,settingsHeight);
    object_setObjectPositionX(settings,240);
    object_setObjectPositionY(settings,530);
    object_setTexturePath(settings,homeScreenRenderer,"images/homeScreen/settings.png");

    PObject exit = object_create();
    object_setTextureWidth(exit,exitWidth);
    object_setTextureHeight(exit,exitHeight);
    object_setObjectRectW(exit,exitWidth);
    object_setObjectRectH(exit,exitHeight);
    object_setObjectPositionW(exit,exitWidth);
    object_setObjectPositionH(exit,exitHeight);
    object_setObjectPositionX(exit,340);
    object_setObjectPositionY(exit,630);
    object_setTexturePath(exit,homeScreenRenderer,"images/homeScreen/exit.png");

    PObject start = object_create();
    object_setTextureWidth(start,startWidth);
    object_setTextureHeight(start,startHeight);
    object_setObjectRectW(start,startWidth);
    object_setObjectRectH(start,startHeight);
    object_setObjectPositionW(start,startWidth);
    object_setObjectPositionH(start,startHeight);
    object_setObjectPositionX(start,310);
    object_setObjectPositionY(start,430);
    object_setTexturePath(start,homeScreenRenderer,"images/homeScreen/start.png");


    PObject settings2 = object_create();
    object_setTextureWidth(settings2,settingsWidth);
    object_setTextureHeight(settings2,settingsHeight);
    object_setObjectRectW(settings2,settingsWidth);
    object_setObjectRectH(settings2,settingsHeight);
    object_setObjectPositionW(settings2,settingsWidth);
    object_setObjectPositionH(settings2,settingsHeight);
    object_setObjectPositionX(settings2,240);
    object_setObjectPositionY(settings2,530);
    object_setTexturePath(settings2,homeScreenRenderer,"images/homeScreen/settings2.png");

    PObject exit2 = object_create();
    object_setTextureWidth(exit2,exitWidth);
    object_setTextureHeight(exit2,exitHeight);
    object_setObjectRectW(exit2,exitWidth);
    object_setObjectRectH(exit2,exitHeight);
    object_setObjectPositionW(exit2,exitWidth);
    object_setObjectPositionH(exit2,exitHeight);
    object_setObjectPositionX(exit2,340);
    object_setObjectPositionY(exit2,630);
    object_setTexturePath(exit2,homeScreenRenderer,"images/homeScreen/exit2.png");

    PObject start2 = object_create();
    object_setTextureWidth(start2,startWidth);
    object_setTextureHeight(start2,startHeight);
    object_setObjectRectW(start2,startWidth);
    object_setObjectRectH(start2,startHeight);
    object_setObjectPositionW(start2,startWidth);
    object_setObjectPositionH(start2,startHeight);
    object_setObjectPositionX(start2,310);
    object_setObjectPositionY(start2,430);
    object_setTexturePath(start2,homeScreenRenderer,"images/homeScreen/start2.png");

    int currentChoose = 1;

    bool currentChanged = false;
    bool direction = true;

    swapValues(&start,&start2);

    while(homeScreenRunning) {

        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;

        homeScreenTime += deltaTime;

        if(homeScreenTime>=1 && homeScreenTime <= 2) {
            object_setLeft(logo,true);
        } else if(homeScreenTime >= 2){
            object_setLeft(logo,false);
            homeScreenTime = 0;
        }

        while(SDL_PollEvent(&homeScreenEvent)) {
            if(homeScreenEvent.type == SDL_QUIT) {
                running = false;
                homeScreenRunning = false;
                choosePlayerRunning = false;
            }
            if(homeScreenEvent.type == SDL_KEYDOWN) {
                if(homeScreenEvent.key.keysym.sym == SDLK_DOWN) {
                    currentChoose++;
                    currentChanged = true;
                    direction = true;
                    if(currentChoose > 3) {
                        currentChoose = 1;
                    }
                } else if(homeScreenEvent.key.keysym.sym == SDLK_UP) {
                        currentChoose--;
                        currentChanged = true;
                        direction = false;
                        if(currentChoose < 1) {
                            currentChoose = 3;
                        }
                } else if(homeScreenEvent.key.keysym.sym == SDLK_RETURN) {
                        switch(currentChoose) {
                        case 1: homeScreenRunning = false; break;
                        case 2: break;
                        case 3: running = false; choosePlayerRunning = false; homeScreenRunning = false; break;
                        }
                }
            }
        }

        if(currentChanged == true) {
            switch(currentChoose){
            case 2:

                        if(direction) {
                            swapValues(&start,&start2);
                            swapValues(&settings,&settings2);
                        } else if(!direction){
                            swapValues(&settings,&settings2);
                            swapValues(&exit,&exit2);
                        }
                break;
            case 3:

                        if(direction){
                            swapValues(&settings,&settings2);
                            swapValues(&exit,&exit2);
                        } else if(!direction){
                            swapValues(&exit,&exit2);
                            swapValues(&start,&start2);
                        }
                break;
            case 1:
                        if(direction){
                            swapValues(&exit,&exit2);
                            swapValues(&start,&start2);
                        }else if(!direction){
                            swapValues(&start,&start2);
                            swapValues(&settings,&settings2);
                        }
                break;
            }
            currentChanged = false;
        }

        SDL_RenderCopy(homeScreenRenderer,homeScreenBackground,NULL,NULL);

        animation_create(object_getPFrameTime(logo),object_getObjectRectPY(logo),object_getObjectRectPX(logo),0,-logoHeight,0,0.5f,logoHeight);

        animation_create(object_getPFrameTime(text),object_getObjectRectPY(text),object_getObjectRectPX(text),0,-textHeight,0,0.5f,textHeight);
        animation_create(object_getPFrameTime(start),object_getObjectRectPY(start),object_getObjectRectPX(start),0,-startHeight,0,0.5f,startHeight);
        animation_create(object_getPFrameTime(exit),object_getObjectRectPY(exit),object_getObjectRectPX(exit),0,-exitHeight,0,0.5f,exitHeight);
        animation_create(object_getPFrameTime(settings),object_getObjectRectPY(settings),object_getObjectRectPX(settings),0,-settingsHeight,0,0.5f,settingsHeight);

        animation_show(homeScreenRenderer,NULL,logo,object_getLeft(logo));
        animation_show(homeScreenRenderer,NULL,text,object_getLeft(text));
        animation_show(homeScreenRenderer,NULL,settings,object_getLeft(settings));
        animation_show(homeScreenRenderer,NULL,start,object_getLeft(start));
        animation_show(homeScreenRenderer,NULL,exit,object_getLeft(exit));

        SDL_RenderPresent(homeScreenRenderer);

    }

    SDL_DestroyRenderer(homeScreenRenderer);
    SDL_DestroyTexture(homeScreenBackground);
    SDL_DestroyWindow(homeScreenWindow);

    homeScreenBackground = NULL;
    homeScreenWindow = NULL;
    homeScreenRenderer = NULL;

    object_objectRemove(start);
    object_objectRemove(start2);
    start = NULL;
    start2 = NULL;

    object_objectRemove(exit);
    object_objectRemove(exit2);
    exit = NULL;
    exit2 = NULL;

    object_objectRemove(settings);
    object_objectRemove(settings2);
    settings = NULL;
    settings2 = NULL;

    object_objectRemove(text);
    object_objectRemove(logo);
    text = NULL;
    logo = NULL;

    float gravityTimer = 0;


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
    player_setJumpTime(player1,rin_jumpDelay);
    player_setOnGround(player1,true);
    player_setPlayerPositionX(player1,300);
    player_setPlayerPositionY(player1,300);
    player_setTexturePath(player1,renderer,"images/rin/rin_nohararight.png");

    PPlayer player2 = player_create();
    player_setTextureWidth(player2,rin_textureWidth);
    player_setTextureHeight(player2,rin_textureHeight);
    player_setPlayerRectW(player2,rin_frameWidth);
    player_setPlayerRectH(player2,rin_frameWidth);
    player_setPlayerPositionW(player2,rin_characterWidth);
    player_setPlayerPositionH(player2,rin_characterHeight);
    player_setLeft(player2,true);
    player_setCurDoing(player2,0);
    player_setMoveSpeed(player2,300.0f);
    player_setJumpTime(player2,rin_jumpDelay);
    player_setOnGround(player2,true);
    player_setPlayerPositionX(player2,1500);
    player_setPlayerPositionY(player2,300);
    player_setTexturePath(player2,renderer,"images/rin/rin_nohararight.png");

    PObject ground1 = object_create();
    object_setTextureWidth(ground1,width);
    object_setTextureHeight(ground1,120);
    object_setObjectRectW(ground1,width);
    object_setObjectRectH(ground1,120);
    object_setObjectPositionW(ground1,width);
    object_setObjectPositionH(ground1,120);
    object_setObjectPositionX(ground1,0);
    object_setObjectPositionY(ground1,470);
    object_setTexturePath(ground1,renderer,"images/background1/ground1.png");

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

    PObject cloud = object_create();
    object_setTextureWidth(cloud,cloud_textureWidth);
    object_setTextureHeight(cloud,cloud_textureHeight);
    object_setObjectRectW(cloud,cloud_frameWidth);
    object_setObjectRectH(cloud,cloud_frameHeight);
    object_setObjectPositionW(cloud,cloud_Width);
    object_setObjectPositionH(cloud,cloud_Height);
    object_setObjectPositionX(cloud,500);
    object_setObjectPositionY(cloud,30);
    object_setTexturePath(cloud,renderer,"images/background1/cloud.png");

    while(running && initializedSucces == true) {

        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_CONTROLLERBUTTONDOWN) {
                if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A ) {
                    if(player_getDead(player1)==false) {
                        player_setCanJump(player1,true);
                        player_setCurDoing(player1,6);
                     }
                } else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {

                } else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {

                } else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {

                }
            } else if(event.type == SDL_CONTROLLERAXISMOTION) {
                //if(event.caxis.value )
            }else if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON_LEFT){

                } else if(event.button.button == SDL_BUTTON_RIGHT) {

                }
            } else if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                case SDLK_u:
                    player_setHealth(player1,player_getHealth(player1)-10);
                    break;
                }
            } else if(event.type == SDL_MOUSEMOTION) {
                //printf("X: %d | Y: %d\n",event.motion.x, event.motion.y);
            }
        }
        if(state[SDL_SCANCODE_RCTRL]) {
            if(player_getDead(player2)==false) {
                player_setCanJump(player2,true);
                player_setCurDoing(player2,6);
            }
        }
        if(state[SDL_SCANCODE_KP_4]) {
               if(player_getDead(player2)==false) {
                    player_setCurDoing(player2,3);
                    player_setIsHitting(player2,true);
                    player_setIsDoneHitting(player2,false);
                }
        } else if(state[SDL_SCANCODE_RIGHT]) {
            if(player_getDead(player2)==false) {
                if(state[SDL_SCANCODE_RSHIFT]) {
                    int currentX = (player_getPlayerPositionX(player2) + ((player_getMoveSpeed(player2)+150) * deltaTime));
                    player_setPlayerPositionX(player2,currentX);
                    player_setCurDoing(player2,5);
                    player_setLeft(player2,false);
                } else if(!state[SDL_SCANCODE_RSHIFT]) {
                    int currentX = player_getPlayerPositionX(player2) + (player_getMoveSpeed(player2) * deltaTime);
                    player_setPlayerPositionX(player2,currentX);
                    player_setCurDoing(player2,1);
                    player_setLeft(player2,false);
                }
            }
        }else  if(state[SDL_SCANCODE_LEFT]) {
            if(player_getDead(player2)==false) {
                if(state[SDL_SCANCODE_RSHIFT]) {
                    int currentX = (player_getPlayerPositionX(player2) - ((player_getMoveSpeed(player2)+150) * deltaTime));
                    player_setPlayerPositionX(player2,currentX);
                    player_setCurDoing(player2,5);
                    player_setLeft(player2,true);
                } else if(!state[SDL_SCANCODE_RSHIFT]) {
                    int currentX = player_getPlayerPositionX(player2) - (player_getMoveSpeed(player2) * deltaTime);
                    player_setPlayerPositionX(player2,currentX);
                    player_setCurDoing(player2,0);
                    player_setLeft(player2,true);
                }
            }
        } else if(!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT] && player_getOnGround(player2)==true&& player_getIsDoneHitting(player2) == true) {
             if(player_getDead(player2)==false) {
                   player_setCurDoing(player2,2);
            }
        }

        if(state[SDL_SCANCODE_SPACE]) {
            if(player_getDead(player1)==false) {
                player_setCanJump(player1,true);
                player_setCurDoing(player1,6);
            }
        }
        if(state[SDL_SCANCODE_F]) {
            if(player_getDead(player1)==false) {
                    player_setCurDoing(player1,3);
                    player_setIsHitting(player1,true);
                    player_setIsDoneHitting(player1,false);
            }
        } else if(state[SDL_SCANCODE_D]) {
            if(player_getDead(player1)==false) {
                if(state[SDL_SCANCODE_LSHIFT]) {
                    int currentX = (player_getPlayerPositionX(player1) + ((player_getMoveSpeed(player1)+150) * deltaTime));
                    player_setPlayerPositionX(player1,currentX);
                    player_setCurDoing(player1,5);
                    player_setLeft(player1,false);
                } else if(!state[SDL_SCANCODE_LSHIFT]) {
                    int currentX = player_getPlayerPositionX(player1) + (player_getMoveSpeed(player1) * deltaTime);
                    player_setPlayerPositionX(player1,currentX);
                    player_setCurDoing(player1,1);
                    player_setLeft(player1,false);
                }
            }
        }else  if(state[SDL_SCANCODE_A]) {
            if(player_getDead(player1)==false) {
                if(state[SDL_SCANCODE_LSHIFT]) {
                    int currentX = (player_getPlayerPositionX(player1) - ((player_getMoveSpeed(player1)+150) * deltaTime));
                    player_setPlayerPositionX(player1,currentX);
                    player_setCurDoing(player1,5);
                    player_setLeft(player1,true);
                } else if(!state[SDL_SCANCODE_LSHIFT]) {
                    int currentX = player_getPlayerPositionX(player1) - (player_getMoveSpeed(player1) * deltaTime);
                    player_setPlayerPositionX(player1,currentX);
                    player_setCurDoing(player1,0);
                    player_setLeft(player1,true);
                }
            }
        } else if(!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D] && player_getOnGround(player1)==true && player_getIsDoneHitting(player1) == true) {
             if(player_getDead(player1)==false) {
                    player_setCurDoing(player1,2);
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

        //printf("%f\n",currentTime*deltaTime);


        if((engine_playerCollision(player1,player2) == 1) && player_getLeft(player1)==false) {
            player_setCanHit(player1,true);
        } else if((engine_playerCollision(player1,player2) == 2) && player_getLeft(player1)==true) {
            player_setCanHit(player1,true);
        } else {
            player_setCanHit(player1,false);
        }

        if(engine_playerCollision(player2,player1) == 1 && player_getLeft(player2)==false) {
            player_setCanHit(player2,true);
        } else if((engine_playerCollision(player2,player1) == 2) && player_getLeft(player2)==true) {
            player_setCanHit(player2,true);
        } else {
            player_setCanHit(player2,false);
        }

        player_hit(player1,-100,300);
        player_hit(player2,-100,300);

        engine_outSideMap(player1);
        engine_outSideMap(player2);
        player_jump(player1,deltaTime);
        player_jump(player2,deltaTime);
        engine_gravity(&gravityTimer,deltaTime, player1, ground1 );
        engine_gravity(&gravityTimer,deltaTime, player2, ground1 );
        engine_clouds(cloud,deltaTime);

        object_setFrameTime(river,object_getFrameTime(river)+deltaTime);
        object_setFrameTime(cloud,object_getFrameTime(cloud)+deltaTime);
        player_setFrameTime(player1, player_getFrameTime(player1)+deltaTime);
        player_setFrameTime(player2, player_getFrameTime(player2)+deltaTime);

        switch(player_getCurDoing(player1)) {
            case 0: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,6200,6700,0.15f,rin_frameHeight); break;
            case 1: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,6200,6700,0.15f,rin_frameHeight); break;
            case 2: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,5200,5700,0.25f,rin_frameHeight); break;
            case 4: if(player_getDead(player1)==false || player_getPlayerRectY(player1) != 1800) { animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),4,1400,1800,0.1f,rin_frameHeight); } player_setDead(player1,true); break;
            case 5: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,4600,5200,0.15f,rin_frameHeight); break;
            case 6: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),5,4100,4600,0.15f,rin_frameHeight); break;
            case 3: animation_create(player_getPFrameTime(player1),player_getPlayerRectPY(player1),player_getPlayerRectPX(player1),4,-100,300,0.10f,rin_frameHeight); break;
        }

        switch(player_getCurDoing(player2)) {
            case 0: animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),5,6200,6700,0.15f,rin_frameHeight); break;
            case 1: animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),5,6200,6700,0.15f,rin_frameHeight); break;
            case 2: animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),5,5200,5700,0.25f,rin_frameHeight); break;
            case 4: if(player_getDead(player2)==false || player_getPlayerRectY(player2) != 1800) { animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),4,1400,1800,0.1f,rin_frameHeight); } player_setDead(player2,true); break;
            case 5: animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),5,4600,5200,0.15f,rin_frameHeight); break;
            case 6: animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),5,4100,4600,0.15f,rin_frameHeight); break;
            case 3: animation_create(player_getPFrameTime(player2),player_getPlayerRectPY(player2),player_getPlayerRectPX(player2),4,-100,300,0.10f,rin_frameHeight); break;
        }

        animation_create(object_getPFrameTime(river),object_getObjectRectPY(river),object_getObjectRectPX(river),3,-111,222,0.5f,river_frameHeight);
        animation_create(object_getPFrameTime(ground1),object_getObjectRectPY(ground1),object_getObjectRectPX(ground1),0,-46,0,0.5f,46);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
        animation_show(renderer,NULL,ground1,object_getLeft(ground1));
        animation_show(renderer,NULL,river,object_getLeft(river));
        animation_show(renderer,NULL,cloud,object_getLeft(cloud));
        animation_show(renderer,player1,NULL,player_getLeft(player1));
        animation_show(renderer,player2,NULL,player_getLeft(player2));
        SDL_RenderPresent(renderer);
    }
    player_playerRemove(player1);
    player1 = NULL;
    player_playerRemove(player2);
    player2 = NULL;

    object_objectRemove(river);
    river = NULL;
    object_objectRemove(ground1);
    ground1 = NULL;
    object_objectRemove(cloud);
    cloud = NULL;

    SDL_GameControllerClose(controller1);
    controller1 = NULL;

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
