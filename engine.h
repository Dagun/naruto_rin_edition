#pragma once
#include <SDL.h>
#include "player.h"
#include "object.h"

void engine_gravity(float *frameTime, float deltaTime, PPlayer ply, PObject obj);
int engine_collisionGround(PPlayer ply, PObject obj);
void engine_outSideMap(PPlayer ply);
void engine_clouds(PObject obj);
int engine_playerCollision(PPlayer ply, PPlayer ply2);
