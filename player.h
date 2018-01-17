#pragma once
#include "SDL.h"
#include "utilities.h"
#include "stdbool.h"

typedef struct player *PPlayer;

PPlayer player_create();

bool player_getDealDamage(PPlayer player);
void player_setDealDamage(PPlayer player, bool value);

bool player_getCanHit(PPlayer player);
void player_setCanHit(PPlayer player, bool value);

void player_jump(PPlayer player, float deltaTime);

void player_setOnGround(PPlayer player, bool value);
bool player_getOnGround(PPlayer player);
void player_setIsDoneJump(PPlayer player, bool value);
bool player_getIsDoneJump(PPlayer player);
void player_setCanJump(PPlayer player, bool value);
bool player_getCanJump(PPlayer player);
void player_setJumpTime(PPlayer player, float value);
float player_getJumpTime(PPlayer player);
bool player_getDead(PPlayer player);
int player_getHealth(PPlayer player);
float* player_getPFrameTime(PPlayer player);
float player_getFrameTime(PPlayer player);
bool player_getLeft(PPlayer player);
float player_getMoveSpeed(PPlayer player);
int player_getCurDoing(PPlayer player);
int player_getTextureHeight(PPlayer player);
int player_getTextureWidth(PPlayer player);
SDL_Texture* player_getTexture(PPlayer player);
SDL_Rect* player_getPlayerRect(PPlayer player);
SDL_Rect* player_getPlayerPosition(PPlayer player);
int player_getPlayerPositionY(PPlayer player);
int player_getPlayerPositionX(PPlayer player);
int* player_getPlayerRectPX(PPlayer player);
int* player_getPlayerRectPY(PPlayer player);
int player_getPlayerRectX(PPlayer player);
int player_getPlayerRectY(PPlayer player);

int player_hit(PPlayer player,PPlayer player2, int frameBegin, int frameEnd);

void player_setIsDoneHitting(PPlayer player, bool value);
bool player_getIsDoneHitting(PPlayer player);

void player_setIsHitting(PPlayer player, bool value);
bool player_getIsHitting(PPlayer player);

void player_setDead(PPlayer player, bool value);
void player_setHealth(PPlayer player, int value);
void player_setFrameTime(PPlayer player, float value);
void player_setLeft(PPlayer player, bool value);
void player_setPlayerRectX(PPlayer player, int value);
void player_setPlayerRectY(PPlayer player, int value);
void player_setPlayerRectW(PPlayer player, int value);
void player_setPlayerRectH(PPlayer player, int value);
void player_setMoveSpeed(PPlayer player, float value);
void player_setCurDoing(PPlayer player, int value);
void player_setTextureHeight(PPlayer player, int value);
void player_setTextureWidth(PPlayer player, int value);
void player_setTexture(PPlayer player, SDL_Texture* value);
void player_setPlayerRect(PPlayer player, SDL_Rect value);
void player_setPlayerPosition(PPlayer player, SDL_Rect value);
void player_setPlayerPositionX(PPlayer player, int value);
void player_setPlayerPositionY(PPlayer player, int value);
void player_setPlayerPositionW(PPlayer player, int value);
void player_setPlayerPositionH(PPlayer player, int value);
void player_setTexturePath(PPlayer player, SDL_Renderer* renderer, char* path);

void player_playerRemove(PPlayer player);
