#include "animation.h"

void animation(float *frameTime,int *y,int *x,int frames,int frameBegin, int frameEnd,float speed, int frameHeight)
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
