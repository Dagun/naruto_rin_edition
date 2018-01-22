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
#include <stdbool.h>

typedef struct object *PObject;

PObject object_create();

float* object_getPFrameTime(PObject object);
float object_getFrameTime(PObject object);
void object_setFrameTime(PObject object, float value);

bool object_getLeft(PObject object);
void object_setLeft(PObject object, bool value);

float object_getMoveSpeed(PObject object);
void object_setMoveSpeed(PObject object, float value);

int object_getCurDoing(PObject object);
void object_setCurDoing(PObject object, int value);

int object_getTextureHeight(PObject object);
void object_setTextureHeight(PObject object, int value);

int object_getTextureWidth(PObject object);
void object_setTextureWidth(PObject object, int value);

SDL_Texture* object_getTexture(PObject object);
void object_setTexture(PObject object, SDL_Texture* value);

SDL_Rect* object_getObjectRect(PObject object);
void object_setObjectRect(PObject object, SDL_Rect value);

SDL_Rect* object_getObjectPosition(PObject object);
void object_setObjectPosition(PObject object, SDL_Rect value);
void object_setObjectPositionY(PObject object, int value);
void object_setObjectPositionX(PObject object, int value);
void object_setObjectPositionW(PObject object, int value);
void object_setObjectPositionH(PObject object, int value);

void object_setObjectRectX(PObject object, int value);
int object_getObjectRectPX(PObject object);
int object_getObjectRectPY(PObject object);
int object_getObjectRectX(PObject object);
int object_getObjectRectY(PObject object);
int object_getObjectPositionY(PObject object);
int object_getObjectPositionX(PObject object);
void object_setObjectRectY(PObject object, int value);
void object_setObjectRectW(PObject object, int value);
void object_setObjectRectH(PObject object, int value);

void object_setTexturePath(PObject object, SDL_Renderer* renderer, char* path);

void object_objectRemove(PObject object);
