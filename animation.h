#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "player.h"
#include "object.h"
#include "stdbool.h"

void animation_create(float *frameTime,int *y,int frames,int frameBegin,int frameEnd,float speed, int frameHeight);
void animation_show(SDL_Renderer* renderer, PPlayer player, PObject object, bool left);
void animation_clouds(PObject obj);
