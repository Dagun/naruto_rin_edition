#include "player.h"

struct player {
    //int neueVariable;
    //int health;
    float frameTime;
    bool left;
    float moveSpeed;
    int curDoing;
    int textureHeight;
    int textureWidth;
    SDL_Texture *texture;
    SDL_Rect playerRect;
    SDL_Rect playerPosition;
};

PPlayer player_create() {
    PPlayer ply = (PPlayer) malloc(sizeof(struct player));
    //player_setHealth(ply,100);
//    player_setDead(ply,0);
    player_setMoveSpeed(ply,0);
    player_setCurDoing(ply,0);
    player_setTextureHeight(ply,0);
    player_setTextureWidth(ply,0);
    player_setPlayerPositionX(ply,0);
    player_setPlayerPositionY(ply,0);
    player_setPlayerPositionW(ply,0);
    player_setPlayerPositionH(ply,0);

    player_setPlayerRectX(ply,0);
    player_setPlayerRectY(ply,0);
    player_setPlayerRectW(ply,0);
    player_setPlayerRectH(ply,0);

    return ply;
}
/*
void player_setDead(PPlayer player, bool value) {
    player->playerDead = value;
}

bool player_getDead(PPlayer player) {
    return player->playerDead;
}

void player_setHealth(PPlayer player,int value) {
    player->health = value;
}

int player_getHealth(PPlayer player) {
    return player->health;
}
*/
PPlayer player_getPFrameTime(PPlayer player) {
    return &(player->frameTime);
}

void player_setFrameTime(PPlayer player, float value) {
    player->frameTime=value;
}

float player_getFrameTime(PPlayer player) {
    return player->frameTime;
}

void player_setLeft(PPlayer player, bool value) {
    player->left = value;
}

bool player_getLeft(PPlayer player) {
    return player->left;
}

void player_setPlayerRectX(PPlayer player,int value) {
    player->playerRect.x = value;
}

void player_setPlayerRectY(PPlayer player, int value) {
    player->playerRect.y = value;
}


void player_setPlayerRectW(PPlayer player,int value) {
    player->playerRect.w = value;
}

void player_setPlayerRectH(PPlayer player, int value) {
    player->playerRect.h = value;
}

int player_getPlayerRectPX(PPlayer player) {
    return &(player->playerRect.x);
}

int player_getPlayerRectPY(PPlayer player) {
    return &(player->playerRect.y);
}

int player_getPlayerRectX(PPlayer player) {
    return (player->playerRect.x);
}

int player_getPlayerRectY(PPlayer player) {
    return (player->playerRect.y);
}

int player_getPlayerPositionX(PPlayer player) {
    return player->playerPosition.x;
}

int player_getPlayerPositionY(PPlayer player) {
    return player->playerPosition.y;
}

int player_getPlayerPositionH(PPlayer player) {
    return player->playerPosition.h;
}

int player_getPlayerPositionW(PPlayer player) {
    return player->playerPosition.w;
}

void player_setPlayerPositionX(PPlayer player, int value) {
    player->playerPosition.x = value;
}

void player_setPlayerPositionY(PPlayer player, int value) {
    player->playerPosition.y = value;
}

void player_setPlayerPositionH(PPlayer player, int value) {
    player->playerPosition.h = value;
}

void player_setPlayerPositionW(PPlayer player, int value) {
    player->playerPosition.w = value;
}

float player_getMoveSpeed(PPlayer player) {
    return player->moveSpeed;
}

int player_getCurDoing(PPlayer player) {
    return player->curDoing;
}

int player_getTextureHeight(PPlayer player){
    return player->textureHeight;
}

int player_getTextureWidth(PPlayer player){
    return player->textureWidth;
}

SDL_Texture* player_getTexture(PPlayer player) {
    return player->texture;
}

SDL_Rect* player_getPlayerRect(PPlayer player) {
    return &(player->playerRect);
}

SDL_Rect* player_getPlayerPosition(PPlayer player) {
    return &(player->playerPosition);
}


void player_setMoveSpeed(PPlayer player, float value) {
    player->moveSpeed = value;
}

void player_setCurDoing(PPlayer player, int value){
    player->curDoing = value;
}

void player_setTextureHeight(PPlayer player, int value){
    player->textureHeight = value;
}

void player_setTextureWidth(PPlayer player, int value){
    player->textureWidth = value;
}

void player_setTexture(PPlayer player, SDL_Texture* value){
    player->texture = value;
}

void player_setTexturePath(PPlayer player, SDL_Renderer* renderer, char* path) {
    player->texture = LoadTexture(path,renderer);
}
void player_setPlayerRect(PPlayer player, SDL_Rect value){
    player->playerRect = value;
}

void player_setPlayerPosition(PPlayer player, SDL_Rect value){
    player->playerPosition = value;
}

void player_playerRemove(PPlayer player) {
    SDL_DestroyTexture(player->texture);
    free(player);
    player = NULL;
}
