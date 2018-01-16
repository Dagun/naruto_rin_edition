#include "animation.h"

void animation_create(float *frameTime,int *y,int *x,int frames,int frameBegin, int frameEnd,float speed, int frameHeight)
{

    if(*frameTime>= speed) {
        *frameTime=0;
        if(*y >= frameEnd || *y < frameBegin)
        {
            *y = frameBegin;
        }
        *y += frameHeight;
    }
}

void animation_show(SDL_Renderer* renderer, PPlayer player, PObject object, bool left) {
    if(player!=NULL) {
        if(left==false) {
            SDL_RenderCopy(renderer,player_getTexture(player),player_getPlayerRect(player),player_getPlayerPosition(player));
        } else if(left == true) {
            SDL_RenderCopyEx(renderer,player_getTexture(player),player_getPlayerRect(player),player_getPlayerPosition(player),0,NULL,SDL_FLIP_HORIZONTAL);
        }
    } else if(object!=NULL){
        if(left==false) {
            SDL_RenderCopy(renderer,object_getTexture(object),object_getObjectRect(object),object_getObjectPosition(object));
        } else if(left == true) {
            SDL_RenderCopyEx(renderer,object_getTexture(object),object_getObjectRect(object),object_getObjectPosition(object),0,NULL,SDL_FLIP_HORIZONTAL);
        }
    }
}
