#include "animation.h"

void animation_create(float *frameTime,int *y,int frames,int frameBegin, int frameEnd,float speed, int frameHeight){
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

void animation_clouds(PObject obj) {
  if (object_getFrameTime(obj) > 14) {
    object_setFrameTime(obj, 0);
  }
  float tmpFrameTime = object_getFrameTime(obj);
  switch ((int) tmpFrameTime) {
  case 1:
    object_setObjectPositionX(obj, -500);
    break;
  case 2:
    object_setObjectPositionX(obj, -200);
    break;
  case 3:
    object_setObjectPositionX(obj, 0);
    break;
  case 4:
    object_setObjectPositionX(obj, 250);
    break;
  case 5:
    object_setObjectPositionX(obj, 450);
    break;
  case 6:
    object_setObjectPositionX(obj, 500);
    break;
  case 7:
    object_setObjectPositionX(obj, 700);
    break;
  case 8:
    object_setObjectPositionX(obj, 900);
    break;
  case 9:
    object_setObjectPositionX(obj, 1100);
    break;
  case 10:
    object_setObjectPositionX(obj, 1300);
    break;
  case 11:
    object_setObjectPositionX(obj, 1500);
    break;
  case 12:
    object_setObjectPositionX(obj, 1800);
    break;
  case 13:
    object_setObjectPositionX(obj, 2000);
    break;
  case 14:
    object_setObjectPositionX(obj, 2300);
    break;
  }
}
