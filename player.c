#include "player.h"

extern const float rin_jumpDelay;

struct player {
    float frameTime;
    bool left;
    float moveSpeed;
    int curDoing;
    int textureHeight;
    int textureWidth;
    SDL_Texture *texture;
    SDL_Rect playerRect;
    SDL_Rect playerPosition;
    bool playerDead;
    int health;
    float jumpTime;
    bool isDoneJump;
    bool canJump;
    bool onGround;
    bool canHit;
    bool isDoneHitting;
    bool isHitting;
};

bool player_getCanHit(PPlayer player) {
    return player->canHit;
}
void player_setCanHit(PPlayer player, bool value) {
    player->canHit = value;
}

bool player_getIsHitting(PPlayer player) {
    return player->isHitting;
}
void player_setIsHitting(PPlayer player, bool value) {
    player->isHitting = value;
}

PPlayer player_create() {
    PPlayer ply = (PPlayer) malloc(sizeof(struct player));
    player_setHealth(ply,100);
    player_setDead(ply,0);
    player_setMoveSpeed(ply,0);
    player_setCurDoing(ply,0);
    player_setTextureHeight(ply,0);
    player_setTextureWidth(ply,0);
    player_setPlayerPositionX(ply,0);
    player_setPlayerPositionY(ply,0);
    player_setPlayerPositionW(ply,0);
    player_setPlayerPositionH(ply,0);

    player_setIsDoneHitting(ply,true);
    player_setIsHitting(ply,false);
    player_setCanHit(ply,true);

    player_setOnGround(ply,true);
    player_setJumpTime(ply,0);
    player_setCanJump(ply,false);
    player_setIsDoneJump(ply,true);

    player_setPlayerRectX(ply,0);
    player_setPlayerRectY(ply,0);
    player_setPlayerRectW(ply,0);
    player_setPlayerRectH(ply,0);

    return ply;
}

void player_setIsDoneHitting(PPlayer player, bool value) {
    player->isDoneHitting = value;
}

bool player_getIsDoneHitting(PPlayer player) {
    return player->isDoneHitting;
}

void player_setOnGround(PPlayer player, bool value) {
    player->onGround = value;
}

bool player_getOnGround(PPlayer player) {
    return player->onGround;
}

void player_setIsDoneJump(PPlayer player, bool value) {
    player->isDoneJump = value;
}

bool player_getIsDoneJump(PPlayer player) {
    return player->isDoneJump;
}

void player_setCanJump(PPlayer player, bool value) {
    player->canJump = value;
}

bool player_getCanJump(PPlayer player) {
    return player->canJump;
}

int player_hit(PPlayer player, int frameBegin, int frameEnd) {
    if(player_getIsDoneHitting(player)==false && player_getIsHitting(player)==true && player_getCurDoing(player)==3) {
        if(player_getCurDoing(player)==3) {
            if(player_getPlayerRectY(player) <= frameEnd &&  player_getPlayerRectY(player) >= frameBegin) {
                if(player_getPlayerRectY(player) == frameEnd) {
                    player_setIsDoneHitting(player,true);
                    player_setIsHitting(player,false);
                }
            }
        }
    } else {
        player_setIsDoneHitting(player,true);
        player_setIsHitting(player,false);
    }
}

void player_jump(PPlayer player, float deltaTime) {
    if(player_getCanJump(player)==true && player_getOnGround(player) == true || player_getIsDoneJump(player)== false){
        player_setJumpTime(player,player_getJumpTime(player) - deltaTime);
        if(player_getJumpTime(player) < rin_jumpDelay && player_getJumpTime(player)  > 0.01) {
            int tmp = player_getPlayerPositionY(player)-15;
            player_setIsDoneJump(player,false);
            player_setPlayerPositionY(player,tmp);
            player_setCurDoing(player,6);
        } else {
            player_setJumpTime(player,rin_jumpDelay);
            player_setCanJump(player,false);
            player_setIsDoneJump(player,true);
        }
    }
}

void player_setJumpTime(PPlayer player, float value) {
    player->jumpTime = value;
}

float player_getJumpTime(PPlayer player) {
    return player->jumpTime;
}

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

float* player_getPFrameTime(PPlayer player) {
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

int* player_getPlayerRectPX(PPlayer player) {
    return &(player->playerRect.x);
}

int* player_getPlayerRectPY(PPlayer player) {
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

