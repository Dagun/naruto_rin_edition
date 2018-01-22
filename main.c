#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

#include "utilities.h"
#include "animation.h"
#include "player.h"
#include "engine.h"
#include "object.h"

//SOUNDS

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

extern const int unknownHeight;
extern const int unknownWidth;

extern const int background_frameWidth;
extern const int background_frameHeight;
extern const int background_textureWidth;
extern const int background_textureHeight;
extern const int background_characterWidth;
extern const int background_characterHeight;

//RIN CHARACTER
extern const int rin_frameWidth;
extern const int rin_frameHeight;
extern const int rin_textureWidth;
extern const int rin_textureHeight;
extern const int rin_characterWidth;
extern const int rin_characterHeight;
extern const float rin_jumpDelay;

//SEXY JUTSU
extern const int sexyjutsu_frameWidth;
extern const int sexyjutsu_frameHeight;
extern const int sexyjutsu_textureWidth;
extern const int sexyjutsu_textureHeight;
extern const int sexyjutsu_characterWidth;
extern const int sexyjutsu_characterHeight;

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


int main(int argc, char* argv[])
{

    bool initializedSucces = true;
    bool retry = true;
    bool clicked = false;

    initializeSDL(&initializedSucces);

    SDL_GameController *controller1 = NULL;
    if(SDL_NumJoysticks() < 1)
    {
        printf("No controller found!\n");
    }
    else
    {
        controller1 = SDL_GameControllerOpen(0);
        if(controller1 == NULL)
        {
            printf("Cannot connect with controller: SDL ERROR: %s",SDL_GetError());
        }
    }

    //Mix_Init(MIX_INIT_MP3);

    int audio_rate = 44100;
    Uint16 audio_format = MIX_DEFAULT_FORMAT;
    int audio_channels = 2;
    int audio_buffers = 2048;

    if(Mix_OpenAudio(audio_rate, AUDIO_S16SYS,audio_channels,audio_buffers) < 0) {
        initializedSucces = false;
        printf("SDL_mixer coudlnt initzialise: %s\n",Mix_GetError());
    }
    Mix_Music *backgroundSound = Mix_LoadMUS("music/mn.wav");
    Mix_Chunk *combo1 = Mix_LoadWAV("music/combo1.wav");

    Mix_PlayMusic(backgroundSound,-1);

    while(retry)
    {
        int prevTime = 0;
        int currentTime = 0;
        float deltaTime = 0;

        float homeScreenTime=0;
        bool runSettings = false;

        bool homeScreenRunning = true;
        bool choosePlayerRunning = true;
        bool running = true;

        SDL_Window *homeScreenWindow= SDL_CreateWindow("Naruto: Rin Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, widthHomeScreen, heightHomeScreen,SDL_WINDOW_SHOWN);
        SDL_Renderer *homeScreenRenderer = SDL_CreateRenderer(homeScreenWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_Event homeScreenEvent;

        retry = false;

        PObject sexyjutsu = object_create();
        object_setFrameTime(sexyjutsu,0);
        object_setTextureWidth(sexyjutsu,sexyjutsu_textureWidth);
        object_setTextureHeight(sexyjutsu,sexyjutsu_textureHeight);
        object_setObjectRectW(sexyjutsu,sexyjutsu_frameWidth);
        object_setObjectRectH(sexyjutsu,sexyjutsu_frameHeight);
        object_setObjectPositionW(sexyjutsu,sexyjutsu_characterWidth);
        object_setObjectPositionH(sexyjutsu,sexyjutsu_characterHeight);
        object_setObjectPositionX(sexyjutsu,40);
        object_setObjectPositionY(sexyjutsu,500);
        object_setTexturePath(sexyjutsu,homeScreenRenderer,"images/sexyjutsu/sexyjutsu.png");

        PObject background2 = object_create();
        object_setFrameTime(background2,0);
        object_setTextureWidth(background2,background_textureWidth);
        object_setTextureHeight(background2,background_textureHeight);
        object_setObjectRectW(background2,background_frameWidth);
        object_setObjectRectH(background2,background_frameHeight);
        object_setObjectPositionW(background2,background_characterWidth);
        object_setObjectPositionH(background2,background_characterHeight);
        object_setObjectPositionX(background2,0);
        object_setObjectPositionY(background2,0);
        object_setTexturePath(background2,homeScreenRenderer,"images/homeScreen/background.png");

        PObject unknown = object_create();
        object_setTextureWidth(unknown,unknownWidth);
        object_setTextureHeight(unknown,unknownHeight);
        object_setObjectRectW(unknown,unknownWidth);
        object_setObjectRectH(unknown,unknownHeight);
        object_setObjectPositionW(unknown,unknownWidth);
        object_setObjectPositionH(unknown,unknownHeight);
        object_setObjectPositionX(unknown,200);
        object_setObjectPositionY(unknown,430);
        object_setTexturePath(unknown,homeScreenRenderer,"images/homeScreen/unknown.png");

        PObject unknown2 = object_create();
        object_setTextureWidth(unknown2,unknownWidth);
        object_setTextureHeight(unknown2,unknownHeight);
        object_setObjectRectW(unknown2,unknownWidth);
        object_setObjectRectH(unknown2,unknownHeight);
        object_setObjectPositionW(unknown2,unknownWidth);
        object_setObjectPositionH(unknown2,unknownHeight);
        object_setObjectPositionX(unknown2,200);
        object_setObjectPositionY(unknown2,430);
        object_setTexturePath(unknown2,homeScreenRenderer,"images/homeScreen/unknown2.png");

        PObject unknown3 = object_create();
        object_setTextureWidth(unknown3,unknownWidth);
        object_setTextureHeight(unknown3,unknownHeight);
        object_setObjectRectW(unknown3,unknownWidth);
        object_setObjectRectH(unknown3,unknownHeight);
        object_setObjectPositionW(unknown3,unknownWidth);
        object_setObjectPositionH(unknown3,unknownHeight);
        object_setObjectPositionX(unknown3,200);
        object_setObjectPositionY(unknown3,530);
        object_setTexturePath(unknown3,homeScreenRenderer,"images/homeScreen/unknown.png");

        PObject unknown4 = object_create();
        object_setTextureWidth(unknown4,unknownWidth);
        object_setTextureHeight(unknown4,unknownHeight);
        object_setObjectRectW(unknown4,unknownWidth);
        object_setObjectRectH(unknown4,unknownHeight);
        object_setObjectPositionW(unknown4,unknownWidth);
        object_setObjectPositionH(unknown4,unknownHeight);
        object_setObjectPositionX(unknown4,200);
        object_setObjectPositionY(unknown4,530);
        object_setTexturePath(unknown4,homeScreenRenderer,"images/homeScreen/unknown2.png");

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

        int homeScreenAnimationShow = 1;

        bool currentChanged = false;
        bool direction = true;

        swapValues(&start,&start2);

        while(homeScreenRunning)
        {

            prevTime = currentTime;
            currentTime = SDL_GetTicks();
            deltaTime = (currentTime - prevTime) / 1000.0f;

            player_setFrameTime(background2, player_getFrameTime(background2)+deltaTime);
            player_setFrameTime(sexyjutsu, player_getFrameTime(sexyjutsu)+deltaTime);
            homeScreenTime += deltaTime;

            if(homeScreenTime>=1 && homeScreenTime <= 2)
            {
                object_setLeft(logo,true);
            }
            else if(homeScreenTime >= 2)
            {
                object_setLeft(logo,false);
                homeScreenTime = 0;
            }

            object_setObjectPositionY(logo,230);
            object_setObjectPositionX(sexyjutsu,40);
            object_setLeft(sexyjutsu,false);

            while(SDL_PollEvent(&homeScreenEvent))
            {
                if(homeScreenEvent.type == SDL_QUIT)
                {
                    running = false;
                    homeScreenRunning = false;
                    choosePlayerRunning = false;
                }
                else if(homeScreenEvent.type == SDL_MOUSEMOTION)
                {
                    //printf("X: %d | Y: %d\n",homeScreenEvent.motion.x, homeScreenEvent.motion.y);
                    if(homeScreenEvent.motion.x > 220 && homeScreenEvent.motion.x < 620)
                    {
                        if(homeScreenEvent.motion.y > 400 && homeScreenEvent.motion.y < 520)
                        {
                            if(currentChoose != 1)
                            {
                                if(currentChoose == 3) direction = true;
                                if(currentChoose == 2) direction = false;
                                currentChoose = 1;
                                currentChanged = true;
                            }
                        }
                        else if(homeScreenEvent.motion.y > 520 && homeScreenEvent.motion.y < 620)
                        {
                            if(currentChoose != 2)
                            {
                                if(currentChoose == 1) direction = true;
                                if(currentChoose == 3) direction = false;
                                currentChoose = 2;
                                currentChanged = true;
                            }
                        }
                        else if(homeScreenEvent.motion.y > 620 && homeScreenEvent.motion.y < 720)
                        {
                            if(currentChoose != 3)
                            {
                                if(currentChoose == 1) direction = false;
                                if(currentChoose==2) direction = true;
                                currentChoose = 3;
                                currentChanged = true;
                            }
                        }
                    }
                }
                else if(homeScreenEvent.type == SDL_MOUSEBUTTONUP)
                {
                    if(homeScreenEvent.button.button == SDL_BUTTON_LEFT)
                    {
                        if(clicked == false) {
                            clicked = true;
                            goto return1;
                        } else {
                            clicked = false;
                        }
                    }
                }
                if(homeScreenEvent.type == SDL_KEYUP ||homeScreenEvent.type == SDL_CONTROLLERBUTTONUP)
                {
                    if(homeScreenEvent.key.keysym.sym == SDLK_DOWN|| homeScreenEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
                    {
                        currentChoose++;
                        currentChanged = true;
                        direction = true;
                        if(currentChoose > 3)
                        {
                            currentChoose = 1;
                        }
                    }
                    else if(homeScreenEvent.key.keysym.sym == SDLK_UP || homeScreenEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
                    {
                        currentChoose--;
                        currentChanged = true;
                        direction = false;
                        if(currentChoose < 1)
                        {
                            currentChoose = 3;
                        }
                    }
                    else if(homeScreenEvent.key.keysym.sym == SDLK_RETURN|| homeScreenEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
                    {
                        return1:
                        switch(currentChoose)
                        {
                        case 1:
                            homeScreenRunning = false;
                            break;
                        case 2:
                            homeScreenAnimationShow = 0;
                            runSettings = true;
                            direction = true;
                            swapValues(&settings,&settings2);
                            swapValues(&exit,&exit2);
                            object_setObjectPositionY(settings,200);
                            object_setObjectPositionX(sexyjutsu,550);
                            object_setObjectPositionY(logo,40);
                            object_setLeft(sexyjutsu,true);
                            currentChanged = false;
                            currentChoose = 3;
                            while(runSettings==true)
                            {
                                homeScreenTime += deltaTime;
                                prevTime = currentTime;
                                currentTime = SDL_GetTicks();
                                deltaTime = (currentTime - prevTime) / 1000.0f;
                                player_setFrameTime(background2, player_getFrameTime(background2)+deltaTime);
                                player_setFrameTime(sexyjutsu, player_getFrameTime(sexyjutsu)+deltaTime);
                                while(SDL_PollEvent(&homeScreenEvent))
                                {
                                   // printf("%d\n",currentChoose);
                                    if(homeScreenEvent.type == SDL_QUIT)
                                    {
                                        running = false;
                                        homeScreenRunning = false;
                                        choosePlayerRunning = false;
                                        runSettings=false;
                                    }
                                    if(homeScreenEvent.type == SDL_MOUSEMOTION)
                                    {
                                        if(homeScreenEvent.motion.x > 220 && homeScreenEvent.motion.x < 620)
                                        {
                                            if(homeScreenEvent.motion.y > 400 && homeScreenEvent.motion.y < 520)
                                            {
                                                if(currentChoose != 1)
                                                {
                                                    if(currentChoose == 3) direction = true;
                                                    if(currentChoose == 2) direction = false;
                                                    currentChoose = 1;
                                                    currentChanged = true;
                                                }
                                            }
                                            else if(homeScreenEvent.motion.y > 520 && homeScreenEvent.motion.y < 620)
                                            {
                                                if(currentChoose != 2)
                                                {
                                                    if(currentChoose == 1) direction = true;
                                                    if(currentChoose == 3) direction = false;
                                                    currentChoose = 2;
                                                    currentChanged = true;
                                                }
                                            }
                                            else if(homeScreenEvent.motion.y > 620 && homeScreenEvent.motion.y < 720)
                                            {
                                                if(currentChoose != 3)
                                                {
                                                    if(currentChoose == 1) direction = false;
                                                    if(currentChoose==2) direction = true;
                                                    currentChoose = 3;
                                                    currentChanged = true;
                                                }
                                            }
                                        }
                                    } else if(homeScreenEvent.type == SDL_MOUSEBUTTONUP)
                                {
                                    if(homeScreenEvent.button.button == SDL_BUTTON_LEFT)
                                    {
                                        //if(clicked == false) {
                                         //   clicked = true;
                                            goto return2;
                                      // } else {
                                        //    clicked = false;
                                      //  }

                                    }
                                }
                               else if(homeScreenEvent.type == SDL_KEYDOWN || homeScreenEvent.type == SDL_CONTROLLERBUTTONUP)
                                {
                                if(homeScreenEvent.key.keysym.sym == SDLK_DOWN|| homeScreenEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
                                {
                                    currentChoose++;
                                    currentChanged = true;
                                    direction = true;
                                    if(currentChoose > 3)
                                    {
                                        currentChoose = 1;
                                    }
                                }
                                else if(homeScreenEvent.key.keysym.sym == SDLK_UP|| homeScreenEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
                                {
                                    currentChoose--;
                                    currentChanged = true;
                                    direction = false;
                                    if(currentChoose < 1)
                                    {
                                        currentChoose = 3;
                                    }
                                }
                                else if(homeScreenEvent.key.keysym.sym == SDLK_RETURN|| homeScreenEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
                                {
                                    return2:
                                    switch(currentChoose)
                                    {
                                    case 1:
                                        break;
                                    case 2:
                                        break;
                                    case 3:


                                        swapValues(&exit,&exit2);
                                        object_setObjectPositionY(settings,530);
                                        swapValues(&settings,&settings2);
                                        currentChanged = false;
                                        currentChoose = 2;
                                        runSettings=false;
                                        homeScreenAnimationShow = true;
                                        break;
                                    }
                                }
                            }
                                }


                            if(currentChanged == true)
                            {
                                switch(currentChoose)
                                {
                                case 2:

                                    if(direction)
                                    {
                                        swapValues(&unknown,&unknown2);
                                        swapValues(&unknown3,&unknown4);
                                    }
                                    else if(!direction)
                                    {
                                        swapValues(&unknown3,&unknown4);
                                        swapValues(&exit,&exit2);
                                    }
                                    break;
                                case 3:

                                    if(direction)
                                    {
                                        swapValues(&unknown3,&unknown4);
                                        swapValues(&exit,&exit2);
                                    }
                                    else if(!direction)
                                    {
                                        swapValues(&exit,&exit2);
                                        swapValues(&unknown,&unknown2);
                                    }
                                    break;
                                case 1:
                                    if(direction)
                                    {
                                        swapValues(&exit,&exit2);
                                        swapValues(&unknown,&unknown2);
                                    }
                                    else if(!direction)
                                    {
                                        swapValues(&unknown,&unknown2);
                                        swapValues(&unknown3,&unknown4);
                                    }
                                    break;
                                }
                                currentChanged = false;
                            }

                            if(homeScreenTime>=1 && homeScreenTime <= 2)
                            {
                                object_setLeft(logo,true);
                            }
                            else if(homeScreenTime >= 2)
                            {
                                object_setLeft(logo,false);
                                homeScreenTime = 0;
                            }

                            animation_create(NULL, background2,object_getPFrameTime(background2),object_getObjectRectY(background2),4,-260,780,0.8f,background_frameHeight);
                            animation_create(NULL, sexyjutsu,object_getPFrameTime(sexyjutsu),object_getObjectRectY(sexyjutsu),43,-130,5330,0.25f,sexyjutsu_frameHeight);
                            animation_create(NULL, logo,object_getPFrameTime(logo),object_getObjectRectY(logo),0,-logoHeight,0,0.5f,logoHeight);
                            animation_create(NULL, settings,object_getPFrameTime(settings),object_getObjectRectY(settings),0,-settingsHeight,0,0.5f,settingsHeight);
                            animation_create(NULL, exit,object_getPFrameTime(exit),object_getObjectRectY(exit),0,-exitHeight,0,0.5f,exitHeight);
                            animation_create(NULL, unknown,object_getPFrameTime(unknown),object_getObjectRectY(unknown),0,-unknownHeight,0,0.5f,unknownHeight);
                            animation_create(NULL, unknown3,object_getPFrameTime(unknown3),object_getObjectRectY(unknown3),0,-unknownHeight,0,0.5f,unknownHeight);
                            animation_show(homeScreenRenderer,NULL,background2,object_getLeft(background2));
                            animation_show(homeScreenRenderer,NULL,sexyjutsu,object_getLeft(sexyjutsu));
                            animation_show(homeScreenRenderer,NULL,settings,object_getLeft(settings));
                            animation_show(homeScreenRenderer,NULL,exit,object_getLeft(exit));
                            animation_show(homeScreenRenderer,NULL,unknown,object_getLeft(unknown));
                            animation_show(homeScreenRenderer,NULL,unknown3,object_getLeft(unknown3));
                            animation_show(homeScreenRenderer,NULL,logo,object_getLeft(logo));
                            SDL_RenderPresent(homeScreenRenderer);
                        }
                        break;
                    case 3:
                        running = false;
                        choosePlayerRunning = false;
                        homeScreenRunning = false;
                        break;
                    }
                }
            }


        if(currentChanged == true)
        {
            switch(currentChoose)
            {
            case 2:

                if(direction)
                {
                    swapValues(&start,&start2);
                    swapValues(&settings,&settings2);
                }
                else if(!direction)
                {
                    swapValues(&settings,&settings2);
                    swapValues(&exit,&exit2);
                }
                break;
            case 3:

                if(direction)
                {
                    swapValues(&settings,&settings2);
                    swapValues(&exit,&exit2);
                }
                else if(!direction)
                {
                    swapValues(&exit,&exit2);
                    swapValues(&start,&start2);
                }
                break;
            case 1:
                if(direction)
                {
                    swapValues(&exit,&exit2);
                    swapValues(&start,&start2);
                }
                else if(!direction)
                {
                    swapValues(&start,&start2);
                    swapValues(&settings,&settings2);
                }
                break;
            }
            currentChanged = false;
        }}

        animation_create(NULL, background2,object_getPFrameTime(background2),object_getObjectRectY(background2),4,-260,780,0.8f,background_frameHeight);
        animation_create(NULL, sexyjutsu,object_getPFrameTime(sexyjutsu),object_getObjectRectY(sexyjutsu),42,-130,sexyjutsu_textureHeight-sexyjutsu_frameHeight,0.25f,sexyjutsu_frameHeight);
        animation_create(NULL, logo,object_getPFrameTime(logo),object_getObjectRectY(logo),0,-logoHeight,0,0.5f,logoHeight);

        animation_create(NULL, text,object_getPFrameTime(text),object_getObjectRectY(text),0,-textHeight,0,0.5f,textHeight);
        animation_create(NULL, start,object_getPFrameTime(start),object_getObjectRectY(start),0,-startHeight,0,0.5f,startHeight);
        animation_create(NULL, exit,object_getPFrameTime(exit),object_getObjectRectY(exit),0,-exitHeight,0,0.5f,exitHeight);
        animation_create(NULL, settings,object_getPFrameTime(settings),object_getObjectRectY(settings),0,-settingsHeight,0,0.5f,settingsHeight);

        if(homeScreenAnimationShow == 1)
        {
            animation_show(homeScreenRenderer,NULL,background2,object_getLeft(background2));
            animation_show(homeScreenRenderer,NULL,sexyjutsu,object_getLeft(sexyjutsu));
            animation_show(homeScreenRenderer,NULL,logo,object_getLeft(logo));
            animation_show(homeScreenRenderer,NULL,text,object_getLeft(text));
            animation_show(homeScreenRenderer,NULL,settings,object_getLeft(settings));
            animation_show(homeScreenRenderer,NULL,start,object_getLeft(start));
            animation_show(homeScreenRenderer,NULL,exit,object_getLeft(exit));
        }
        SDL_RenderPresent(homeScreenRenderer);

    }

    SDL_DestroyRenderer(homeScreenRenderer);
    SDL_DestroyWindow(homeScreenWindow);

    homeScreenWindow = NULL;
    homeScreenRenderer = NULL;

    object_objectRemove(start);
    object_objectRemove(start2);
    object_objectRemove(unknown2);
    object_objectRemove(unknown);
    object_objectRemove(unknown3);
    object_objectRemove(unknown4);
    unknown = NULL;
    unknown2 = NULL;
    unknown3 = NULL;
    unknown4 = NULL;
    start = NULL;
    start2 = NULL;

    object_objectRemove(sexyjutsu);
    object_objectRemove(background2);
    background2 = NULL;
    sexyjutsu = NULL;

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

    SDL_Window *window = SDL_CreateWindow("Naruto: Rin Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_BORDERLESS);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    SDL_Texture *background = LoadTexture("images/background1/background.png",renderer);
    if(background == NULL )
    {
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

    PObject transparency = object_create();
    object_setTextureWidth(transparency,100);
    object_setTextureHeight(transparency,100);
    object_setObjectRectW(transparency,100);
    object_setObjectRectH(transparency,100);
    object_setObjectPositionW(transparency,width);
    object_setObjectPositionH(transparency,height);
    object_setObjectPositionX(transparency,0);
    object_setObjectPositionY(transparency,0);
    object_setTexturePath(transparency,renderer,"images/pauseMenu/transparency.png");

    PObject continuetext = object_create();
    object_setTextureWidth(continuetext,442);
    object_setTextureHeight(continuetext,82);
    object_setObjectRectW(continuetext,442);
    object_setObjectRectH(continuetext,82);
    object_setObjectPositionW(continuetext,442);
    object_setObjectPositionH(continuetext,82);
    object_setObjectPositionX(continuetext,750);
    object_setObjectPositionY(continuetext,300);
    object_setTexturePath(continuetext,renderer,"images/pauseMenu/continue.png");

    PObject continuetext2 = object_create();
    object_setTextureWidth(continuetext2,442);
    object_setTextureHeight(continuetext2,82);
    object_setObjectRectW(continuetext2,442);
    object_setObjectRectH(continuetext2,82);
    object_setObjectPositionW(continuetext2,442);
    object_setObjectPositionH(continuetext2,82);
    object_setObjectPositionX(continuetext2,750);
    object_setObjectPositionY(continuetext2,300);
    object_setTexturePath(continuetext2,renderer,"images/pauseMenu/continue2.png");

    PObject exit_2 = object_create();
    object_setTextureWidth(exit_2,161);
    object_setTextureHeight(exit_2,81);
    object_setObjectRectW(exit_2,161);
    object_setObjectRectH(exit_2,81);
    object_setObjectPositionW(exit_2,161);
    object_setObjectPositionH(exit_2,81);
    object_setObjectPositionX(exit_2,870);
    object_setObjectPositionY(exit_2,700);
    object_setTexturePath(exit_2,renderer,"images/pauseMenu/exit.png");

    PObject exit_22 = object_create();
    object_setTextureWidth(exit_22,161);
    object_setTextureHeight(exit_22,81);
    object_setObjectRectW(exit_22,161);
    object_setObjectRectH(exit_22,81);
    object_setObjectPositionW(exit_22,161);
    object_setObjectPositionH(exit_22,81);
    object_setObjectPositionX(exit_22,870);
    object_setObjectPositionY(exit_22,700);
    object_setTexturePath(exit_22,renderer,"images/pauseMenu/exit2.png");

    PObject btm = object_create();
    object_setTextureWidth(btm,616);
    object_setTextureHeight(btm,82);
    object_setObjectRectW(btm,616);
    object_setObjectRectH(btm,82);
    object_setObjectPositionW(btm,616);
    object_setObjectPositionH(btm,82);
    object_setObjectPositionX(btm,650);
    object_setObjectPositionY(btm,500);
    object_setTexturePath(btm,renderer,"images/pauseMenu/btm.png");

    PObject btm2 = object_create();
    object_setTextureWidth(btm2,616);
    object_setTextureHeight(btm2,82);
    object_setObjectRectW(btm2,616);
    object_setObjectRectH(btm2,82);
    object_setObjectPositionW(btm2,616);
    object_setObjectPositionH(btm2,82);
    object_setObjectPositionX(btm2,650);
    object_setObjectPositionY(btm2,500);
    object_setTexturePath(btm2,renderer,"images/pauseMenu/btm2.png");

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
    object_setObjectPositionX(cloud,-600);
    object_setObjectPositionY(cloud,30);
    object_setTexturePath(cloud,renderer,"images/background1/cloud.png");

    PObject p1win = object_create();
    object_setTextureWidth(p1win,161);
    object_setTextureHeight(p1win,81);
    object_setObjectRectW(p1win,161);
    object_setObjectRectH(p1win,81);
    object_setObjectPositionW(p1win,161);
    object_setObjectPositionH(p1win,81);
    object_setObjectPositionX(p1win,870);
    object_setObjectPositionY(p1win,700);
    object_setTexturePath(p1win,renderer,"images/win/p1win.png");

    PObject p1win2= object_create();
    object_setTextureWidth(p1win2,161);
    object_setTextureHeight(p1win2,81);
    object_setObjectRectW(p1win2,161);
    object_setObjectRectH(p1win2,81);
    object_setObjectPositionW(p1win2,161);
    object_setObjectPositionH(p1win2,81);
    object_setObjectPositionX(p1win2,870);
    object_setObjectPositionY(p1win2,700);
    object_setTexturePath(p1win2,renderer,"images/win/p1win2.png");

    PObject p2win = object_create();
    object_setTextureWidth(p2win,161);
    object_setTextureHeight(p2win,81);
    object_setObjectRectW(p2win,161);
    object_setObjectRectH(p2win,81);
    object_setObjectPositionW(p2win,161);
    object_setObjectPositionH(p2win,81);
    object_setObjectPositionX(p2win,870);
    object_setObjectPositionY(p2win,700);
    object_setTexturePath(p2win,renderer,"images/win/p2win.png");


    PObject p2win2 = object_create();
    object_setTextureWidth(p2win2,161);
    object_setTextureHeight(p2win2,81);
    object_setObjectRectW(p2win2,161);
    object_setObjectRectH(p2win2,81);
    object_setObjectPositionW(p2win2,161);
    object_setObjectPositionH(p2win2,81);
    object_setObjectPositionX(p2win2,870);
    object_setObjectPositionY(p2win2,700);
    object_setTexturePath(p2win2,renderer,"images/win/p2win2.png");

    PObject healthbar1 = object_create();
    object_setTextureWidth(healthbar1,600);
    object_setTextureHeight(healthbar1,400);
    object_setObjectRectW(healthbar1,600);
    object_setObjectRectH(healthbar1,400);
    object_setObjectPositionW(healthbar1,350);
    object_setObjectPositionH(healthbar1,150);
    object_setObjectPositionX(healthbar1,50);
    object_setObjectPositionY(healthbar1,900);
    object_setTexturePath(healthbar1,renderer,"images/healthbar.png");

    PObject health1 = object_create();
    object_setTextureWidth(health1,600);
    object_setTextureHeight(health1,400);
    object_setObjectRectW(health1,600);
    object_setObjectRectH(health1,400);
    object_setObjectPositionW(health1,250);
    object_setObjectPositionH(health1,50);
    object_setObjectPositionX(health1,120);
    object_setObjectPositionY(health1,945);
    object_setTexturePath(health1,renderer,"images/health.png");

    PObject healthbar2 = object_create();
    object_setTextureWidth(healthbar2,600);
    object_setTextureHeight(healthbar2,400);
    object_setObjectRectW(healthbar2,600);
    object_setObjectRectH(healthbar2,400);
    object_setObjectPositionW(healthbar2,350);
    object_setObjectPositionH(healthbar2,150);
    object_setObjectPositionX(healthbar2,1500);
    object_setLeft(healthbar2,true);
    object_setObjectPositionY(healthbar2,900);
    object_setTexturePath(healthbar2,renderer,"images/healthbar.png");

    PObject health2 = object_create();
    object_setTextureWidth(health2,600);
    object_setTextureHeight(health2,400);
    object_setObjectRectW(health2,600);
    object_setObjectRectH(health2,400);
    object_setObjectPositionW(health2,250);
    object_setObjectPositionH(health2,50);
    object_setObjectPositionX(health2,1780);
    object_setLeft(health2,true);
    object_setObjectPositionY(health2,945);
    object_setTexturePath(health2,renderer,"images/health.png");

    PObject energybar1 = object_create();
    object_setTextureWidth(energybar1,600);
    object_setTextureHeight(energybar1,400);
    object_setObjectRectW(energybar1,600);
    object_setObjectRectH(energybar1,400);
    object_setObjectPositionW(energybar1,350);
    object_setObjectPositionH(energybar1,150);
    object_setObjectPositionX(energybar1,50);
    object_setObjectPositionY(energybar1,800);
    object_setTexturePath(energybar1,renderer,"images/energybar.png");

    PObject energy1 = object_create();
    object_setTextureWidth(energy1,600);
    object_setTextureHeight(energy1,400);
    object_setObjectRectW(energy1,600);
    object_setObjectRectH(energy1,400);
    object_setObjectPositionW(energy1,250);
    object_setObjectPositionH(energy1,50);
    object_setObjectPositionX(energy1,120);
    object_setObjectPositionY(energy1,845);
    object_setTexturePath(energy1,renderer,"images/energy.png");

    PObject energybar2 = object_create();
    object_setTextureWidth(energybar2,600);
    object_setTextureHeight(energybar2,400);
    object_setObjectRectW(energybar2,600);
    object_setObjectRectH(energybar2,400);
    object_setObjectPositionW(energybar2,350);
    object_setObjectPositionH(energybar2,150);
    object_setObjectPositionX(energybar2,1500);
    object_setLeft(energybar2,true);
    object_setObjectPositionY(energybar2,800);
    object_setTexturePath(energybar2,renderer,"images/energybar.png");

    PObject energy2 = object_create();
    object_setTextureWidth(energy2,600);
    object_setTextureHeight(energy2,400);
    object_setObjectRectW(energy2,600);
    object_setObjectRectH(energy2,400);
    object_setObjectPositionW(energy2,250);
    object_setObjectPositionH(energy2,50);
    object_setObjectPositionX(energy2,1780);
    object_setLeft(energy2,true);
    object_setObjectPositionY(energy2,845);
    object_setTexturePath(energy2,renderer,"images/energy.png");

    bool pause = false;

    swapValues(&continuetext2,&continuetext);

    while(running && initializedSucces == true)
    {

        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // printf("P1: %d | P2: %d\n",player_getHealth(player1),player_getHealth(player2));

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            else if(event.type == SDL_CONTROLLERBUTTONUP)
            {
                if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A )
                {
                    if(pause){
                        switch(currentChoose)
                        {
                        case 1:
                            pause = false;
                            break;
                        case 2:
                            retry = true;
                            pause = false;
                            running = false;
                            clicked = true;
                            break;
                        case 3:
                            running = false;
                            break;
                        }
                        } else {
                    if(player_getDead(player1)==false)
                    {
                        player_setCanJump(player1,true);
                        player_setCurDoing(player1,6);
                    }
                }}
                else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
                {

                }
                else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
                {

                }
                else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
                    player_setCurDoing(player1,3);
                    player_setIsHitting(player1,true);
                    player_setIsDoneHitting(player1,false);
                } else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                    if(pause==true)
                    {
                        pause = false;
                    }
                    else if(pause==false)
                    {
                        pause = true;
                    }
                } else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                    if(pause){
                    currentChoose--;
                    currentChanged = true;
                    direction = false;
                    if(currentChoose < 1)
                    {
                        currentChoose = 3;
                    }
                    }
                } else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
                    if(pause){
                    currentChoose++;
                    currentChanged = true;
                    direction = true;
                    if(currentChoose > 3)
                    {
                        currentChoose = 1;
                    }
                    }
                    break;
                }
            }
            else if(event.type == SDL_CONTROLLERAXISMOTION)
            {
                //printf("%d\n",SDL_GameControllerGetAxis(controller1,SDL_CONTROLLER_AXIS_LEFTX ));
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN && pause)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                   // if(clicked == false) {
                   //     clicked = true;
                   if(pause)
                        goto return3;

                  //  } else if(clicked==true){
                  //      clicked = false;
                   // }
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {

                }
            }
            else if(event.type == SDL_KEYUP)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_u:
                    player_setHealth(player1,player_getHealth(player1)-10);
                    break;
                case SDLK_ESCAPE:
                    if(pause==true)
                    {
                        pause = false;
                    }
                    else if(pause==false)
                    {
                        pause = true;
                    }
                    break;
                case SDLK_DOWN:
                    if(pause){
                    currentChoose++;
                    currentChanged = true;
                    direction = true;
                    if(currentChoose > 3)
                    {
                        currentChoose = 1;
                    }
                    }
                    break;
                case SDLK_UP:
                    if(pause){
                    currentChoose--;
                    currentChanged = true;
                    direction = false;
                    if(currentChoose < 1)
                    {
                        currentChoose = 3;
                    }
                    }
                    break;
                case SDLK_RETURN:
                        return3:
                        if(pause){
                        switch(currentChoose)
                        {
                        case 1:
                            pause = false;
                            break;
                        case 2:
                            retry = true;
                            pause = false;
                            running = false;
                            clicked = true;
                            break;
                        case 3:
                            running = false;
                            break;
                        }
                        }
                    break;
                    case SDLK_f:
                        if(player_getDead(player1)==false)
                            {
                                player_setCurDoing(player1,3);
                                player_setIsHitting(player1,true);
                                player_setIsDoneHitting(player1,false);
                            } break;
                    case SDLK_KP_4:
                        if(player_getDead(player2)==false)
                            {
                                player_setCurDoing(player2,3);
                                player_setIsHitting(player2,true);
                                player_setIsDoneHitting(player2,false);
                            } break;
                }

            }
            else if(event.type == SDL_MOUSEMOTION)
            {
                //printf("%d - %d\n",event.motion.x,event.motion.y);
                if(event.motion.x > 600 && event.motion.x < 1300)
                    {
                        if(event.motion.y > 400 && event.motion.y < 520)
                        {
                            if(currentChoose != 1)
                            {
                                if(currentChoose == 3) direction = true;
                                if(currentChoose == 2) direction = false;
                                currentChoose = 1;
                                currentChanged = true;
                            }
                        }
                        else if(event.motion.y > 520 && event.motion.y < 620)
                        {
                            if(currentChoose != 2)
                            {
                                if(currentChoose == 1) direction = true;
                                if(currentChoose == 3) direction = false;
                                currentChoose = 2;
                                currentChanged = true;
                            }
                        }
                        else if(event.motion.y > 620 && event.motion.y < 720)
                        {
                            if(currentChoose != 3)
                            {
                                if(currentChoose == 1) direction = false;
                                if(currentChoose==2) direction = true;
                                currentChoose = 3;
                                currentChanged = true;
                            }
                        }
                    }
            }
        }
        if(pause==false)
        {
            if(state[SDL_SCANCODE_RCTRL])
            {
                if(player_getDead(player2)==false)
                {
                    player_setCanJump(player2,true);
                    player_setCurDoing(player2,6);
                }
            }

           if(state[SDL_SCANCODE_RIGHT])
            {
                if(player_getDead(player2)==false)
                {
                    if(state[SDL_SCANCODE_RSHIFT])
                    {
                        int currentX = (player_getPlayerPositionX(player2) + ((player_getMoveSpeed(player2)+150) * deltaTime));
                        player_setPlayerPositionX(player2,currentX);
                        player_setCurDoing(player2,5);
                        player_setLeft(player2,false);
                    }
                    else if(!state[SDL_SCANCODE_RSHIFT])
                    {
                        int currentX = player_getPlayerPositionX(player2) + (player_getMoveSpeed(player2) * deltaTime);
                        player_setPlayerPositionX(player2,currentX);
                        player_setCurDoing(player2,1);
                        player_setLeft(player2,false);
                    }
                }
            }
            else  if(state[SDL_SCANCODE_LEFT])
            {
                if(player_getDead(player2)==false)
                {
                    if(state[SDL_SCANCODE_RSHIFT])
                    {
                        int currentX = (player_getPlayerPositionX(player2) - ((player_getMoveSpeed(player2)+150) * deltaTime));
                        player_setPlayerPositionX(player2,currentX);
                        player_setCurDoing(player2,5);
                        player_setLeft(player2,true);
                    }
                    else if(!state[SDL_SCANCODE_RSHIFT])
                    {
                        int currentX = player_getPlayerPositionX(player2) - (player_getMoveSpeed(player2) * deltaTime);
                        player_setPlayerPositionX(player2,currentX);
                        player_setCurDoing(player2,0);
                        player_setLeft(player2,true);
                    }
                }
            }
            else if(!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT] && player_getOnGround(player2)==true&& player_getIsDoneHitting(player2) == true)
            {
                if(player_getDead(player2)==false)
                {
                    player_setCurDoing(player2,2);
                }
            }
            if(state[SDL_SCANCODE_SPACE])
            {
                if(player_getDead(player1)==false)
                {
                    player_setCanJump(player1,true);
                    player_setCurDoing(player1,6);
                }
            }
            if(state[SDL_SCANCODE_D] || SDL_GameControllerGetAxis(controller1,SDL_CONTROLLER_AXIS_LEFTX)  > 100)
            {
                if(player_getDead(player1)==false)
                {
                    if(state[SDL_SCANCODE_LSHIFT] || SDL_GameControllerGetAxis(controller1,SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 1000)
                    {
                        int currentX = (player_getPlayerPositionX(player1) + ((player_getMoveSpeed(player1)+150) * deltaTime));
                        player_setPlayerPositionX(player1,currentX);
                        player_setCurDoing(player1,5);
                        player_setLeft(player1,false);
                    }
                    else if(!state[SDL_SCANCODE_LSHIFT])
                    {
                        int currentX = player_getPlayerPositionX(player1) + (player_getMoveSpeed(player1) * deltaTime);
                        player_setPlayerPositionX(player1,currentX);
                        player_setCurDoing(player1,1);
                        player_setLeft(player1,false);
                    }
                }
            }
            else  if(state[SDL_SCANCODE_A] || SDL_GameControllerGetAxis(controller1,SDL_CONTROLLER_AXIS_LEFTX ) < -100)
            {
                if(player_getDead(player1)==false)
                {
                    if(state[SDL_SCANCODE_LSHIFT]|| SDL_GameControllerGetAxis(controller1,SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 1000)
                    {
                        int currentX = (player_getPlayerPositionX(player1) - ((player_getMoveSpeed(player1)+150) * deltaTime));
                        player_setPlayerPositionX(player1,currentX);
                        player_setCurDoing(player1,5);
                        player_setLeft(player1,true);
                    }
                    else if(!state[SDL_SCANCODE_LSHIFT])
                    {
                        int currentX = player_getPlayerPositionX(player1) - (player_getMoveSpeed(player1) * deltaTime);
                        player_setPlayerPositionX(player1,currentX);
                        player_setCurDoing(player1,0);
                        player_setLeft(player1,true);
                    }
                }
            }
            else if(!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D] && player_getOnGround(player1)==true && player_getIsDoneHitting(player1) == true)
            {
                if(player_getDead(player1)==false)
                {
                    player_setCurDoing(player1,2);
                }
            }
            if(player_getHealth(player1)==0)
            {
                if(player_getPlayerPositionY(player1)==1800)
                {
                    player_setFrameTime(player1,0);
                }
                player_setCurDoing(player1,4);

                //swapValues()
            }
            else
            {
                // printf("%d\n",player_getHealth(player1));
            }
            if(player_getHealth(player2)==0)
            {
                if(player_getPlayerPositionY(player2)==1800)
                {
                    player_setFrameTime(player2,0);
                }
                player_setCurDoing(player2,4);
            }
            else
            {
                // printf("%d\n",player_getHealth(player1));
            }
        }

        //printf("%f\n",currentTime*deltaTime);
        if(currentChanged==true)
        {
            switch(currentChoose)
            {
            case 2:
                if(direction)
                {
                    swapValues(&continuetext2,&continuetext);
                    swapValues(&btm,&btm2);
                }
                else if(!direction)
                {
                    swapValues(&btm,&btm2);
                    swapValues(&exit_2,&exit_22);
                }
                break;
            case 3:

                if(direction)
                {
                    swapValues(&btm,&btm2);
                    swapValues(&exit_2,&exit_22);
                }
                else if(!direction)
                {
                    swapValues(&continuetext,&continuetext2);
                    swapValues(&exit_2,&exit_22);
                }
                break;
            case 1:
                if(direction)
                {
                    swapValues(&exit_2,&exit_22);
                    swapValues(&continuetext2,&continuetext);
                }
                else if(!direction)
                {
                    swapValues(&continuetext,&continuetext2);
                    swapValues(&btm,&btm2);
                }
            }
            currentChanged = false;
        }
        // printf("P1: %d | P2: %d\n\n",player_getHealth(player1),player_getHealth(player2));

        if((engine_playerCollision(player1,player2) == 1) && player_getLeft(player1)==false)
        {
            player_setCanHit(player1,true);
        }
        else if((engine_playerCollision(player1,player2) == 2) && player_getLeft(player1)==true)
        {
            player_setCanHit(player1,true);
        }
        else
        {
            player_setCanHit(player1,false);
        }

        if(engine_playerCollision(player2,player1) == 1 && player_getLeft(player2)==false)
        {
            player_setCanHit(player2,true);
        }
        else if((engine_playerCollision(player2,player1) == 2) && player_getLeft(player2)==true)
        {
            player_setCanHit(player2,true);
        }
        else
        {
            player_setCanHit(player2,false);
        }

        player_hit(player1,player2,-100,300,combo1);
        player_hit(player2,player1,-100,300,combo1);


         engine_outSideMap(player1);
        engine_outSideMap(player2);
        player_jump(player1,deltaTime);
        player_jump(player2,deltaTime);
        engine_gravity(&gravityTimer,deltaTime, player1, ground1 );
        engine_gravity(&gravityTimer,deltaTime, player2, ground1 );
        animation_clouds(cloud);


        if(pause==false)
        {

            object_setFrameTime(river,object_getFrameTime(river)+deltaTime);
            object_setFrameTime(cloud,object_getFrameTime(cloud)+deltaTime);
            player_setFrameTime(player1, player_getFrameTime(player1)+deltaTime);
            player_setFrameTime(player2, player_getFrameTime(player2)+deltaTime);

            object_setObjectPositionW(health1,2.5*player_getHealth(player1));
            object_setObjectPositionW(health2,-2.5*player_getHealth(player2));
            object_setObjectPositionW(energy1,2.5*player_getEnergy(player1));
            object_setObjectPositionW(energy2,-2.5*player_getEnergy(player2));

        }
        if(player_getDead(player1))
        {
            player_setCurDoing(player1,4);
        }
        if(player_getDead(player2))
        {
            player_setCurDoing(player2,4);
        }


        switch(player_getCurDoing(player1))
        {
        case 0:
            animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),5,6200,6700,0.15f,rin_frameHeight);
            break;
        case 1:
            animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),5,6200,6700,0.15f,rin_frameHeight);
            break;
        case 2:
            animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),5,5200,5700,0.25f,rin_frameHeight);
            break;
        case 4:
            if(player_getDead(player1)==false || player_getPlayerRectY(player1) != 1800)
            {
                animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),4,1400,1800,0.1f,rin_frameHeight);
            }
            player_setDead(player1,true);
            break;
        case 5:
            animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),5,4600,5200,0.15f,rin_frameHeight);
            break;
        case 6:
            animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),5,4100,4600,0.15f,rin_frameHeight);
            break;
        case 3:
            animation_create(player1,NULL,player_getPFrameTime(player1),player_getPlayerRectPY(player1),4,-100,300,0.10f,rin_frameHeight);
            break;
        }

        switch(player_getCurDoing(player2))
        {
        case 0:
            animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),5,6200,6700,0.15f,rin_frameHeight);
            break;
        case 1:
            animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),5,6200,6700,0.15f,rin_frameHeight);
            break;
        case 2:
            animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),5,5200,5700,0.25f,rin_frameHeight);
            break;
        case 4:
            if(player_getDead(player2)==false || player_getPlayerRectY(player2) != 1800)
            {
                animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),4,1400,1800,0.1f,rin_frameHeight);
            }
            player_setDead(player2,true);
            break;
        case 5:
            animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),5,4600,5200,0.15f,rin_frameHeight);
            break;
        case 6:
            animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),5,4100,4600,0.15f,rin_frameHeight);
            break;
        case 3:
            animation_create(player2,NULL,player_getPFrameTime(player2),player_getPlayerRectPY(player2),4,-100,300,0.10f,rin_frameHeight);
            break;
        }




        animation_create(NULL, river,object_getPFrameTime(river),object_getObjectRectY(river),3,-111,222,0.5f,river_frameHeight);
        animation_create(NULL, ground1,object_getPFrameTime(ground1),object_getObjectRectY(ground1),0,-46,0,0.5f,46);
        animation_create(NULL, transparency,object_getPFrameTime(transparency),object_getObjectRectY(transparency),0,-100,0,0.15,100);
        animation_create(NULL, exit_2,object_getPFrameTime(exit_2),object_getObjectRectY(exit_2),0,-81,0,0.5f,81);
        animation_create(NULL, btm,object_getPFrameTime(btm),object_getObjectRectY(btm),0,-80,0,0.5f,80);
        animation_create(NULL, continuetext,object_getPFrameTime(continuetext),object_getObjectRectY(continuetext),0,-79,0,0.5f,79);
        animation_create(NULL, healthbar1,object_getPFrameTime(healthbar1),object_getObjectRectY(healthbar1),0,-79,0,0.5f,79);
        animation_create(NULL, health1,object_getPFrameTime(health1),object_getObjectRectY(health1),0,-79,0,0.5f,79);
        animation_create(NULL, healthbar2,object_getPFrameTime(healthbar2),object_getObjectRectY(healthbar2),0,-79,0,0.5f,79);
        animation_create(NULL, health2,object_getPFrameTime(health2),object_getObjectRectY(health2),0,-79,0,0.5f,79);
        animation_create(NULL, energy2,object_getPFrameTime(energy2),object_getObjectRectY(energy2),0,-79,0,0.5f,79);
        animation_create(NULL, energy1,object_getPFrameTime(energy1),object_getObjectRectY(energy1),0,-79,0,0.5f,79);
        animation_create(NULL, energybar1,object_getPFrameTime(energybar1),object_getObjectRectY(energybar1),0,-79,0,0.5f,79);
        animation_create(NULL, energybar2,object_getPFrameTime(energybar2),object_getObjectRectY(energybar2),0,-79,0,0.5f,79);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
        animation_show(renderer,NULL,ground1,object_getLeft(ground1));
        animation_show(renderer,NULL,river,object_getLeft(river));
        animation_show(renderer,NULL,cloud,object_getLeft(cloud));
        animation_show(renderer,player1,NULL,player_getLeft(player1));
        animation_show(renderer,player2,NULL,player_getLeft(player2));
        animation_show(renderer,health1,NULL,player_getLeft(health1));
        animation_show(renderer,healthbar1,NULL,player_getLeft(healthbar1));
        animation_show(renderer,health2,NULL,player_getLeft(health2));
        animation_show(renderer,healthbar2,NULL,player_getLeft(healthbar2));
        animation_show(renderer,energy2,NULL,player_getLeft(energy2));
        animation_show(renderer,energy1,NULL,player_getLeft(energy1));
        animation_show(renderer,energybar1,NULL,player_getLeft(energy1));
        animation_show(renderer,energybar2,NULL,player_getLeft(energy2));

        if(pause==true)
        {

            animation_show(renderer,NULL,transparency,object_getLeft(transparency));
            animation_show(renderer,NULL,exit_2,object_getLeft(exit_2));
            animation_show(renderer,NULL,btm,object_getLeft(btm));
            animation_show(renderer,NULL,continuetext,object_getLeft(continuetext));

        }


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

    object_objectRemove(exit_22);
    object_objectRemove(exit_2);
    object_objectRemove(btm2);
    object_objectRemove(btm);
    object_objectRemove(continuetext2);
    object_objectRemove(continuetext);
    object_objectRemove(transparency);
    object_objectRemove(p1win);
    object_objectRemove(p1win2);
    object_objectRemove(p2win);
    object_objectRemove(p2win2);

    object_objectRemove(health1);
    object_objectRemove(health2);
    object_objectRemove(healthbar1);
    object_objectRemove(healthbar2);
    object_objectRemove(energy1);
    object_objectRemove(energy2);
    object_objectRemove(energybar1);
    object_objectRemove(energybar2);

    p1win = NULL;
    p2win = NULL;
    p1win2 = NULL;
    p2win2 = NULL;
    btm = NULL;
    btm2 = NULL;
    exit_2 = NULL;
    exit_22 = NULL;
    continuetext2 = NULL;
    continuetext = NULL;
    transparency = NULL;

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(background);
    SDL_DestroyWindow(window);

    background = NULL;
    renderer = NULL;
    window = NULL;
}

SDL_GameControllerClose(controller1);
controller1 = NULL;

Mix_FreeMusic(backgroundSound);
Mix_FreeChunk(combo1);
combo1 = NULL;
backgroundSound =NULL;
Mix_CloseAudio();

SDL_Quit();
return 0;
}
