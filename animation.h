#pragma once
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif
#include "player.h"
#include "object.h"
#include "stdbool.h"

void animation_create(PPlayer ply, PObject obj, float *frameTime, int y,
                      int frames, int frameBegin, int frameEnd, float speed,
                      int frameHeight);
void animation_show(SDL_Renderer* renderer, PPlayer player, PObject object, bool left);
void animation_clouds(PObject obj);
