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

void engine_gravity(float *frameTime, float deltaTime, PPlayer ply, PObject obj);
int engine_collisionGround(PPlayer ply, PObject obj);
void engine_outSideMap(PPlayer ply);
int engine_playerCollision(PPlayer ply, PPlayer ply2);
