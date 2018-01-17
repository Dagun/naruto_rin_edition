#include "object.h"

struct object {
    float frameTime;
    bool left;
    float moveSpeed;
    int curDoing;
    int textureHeight;
    int textureWidth;
    SDL_Texture *texture;
    SDL_Rect objectRect;
    SDL_Rect objectPosition;
};

PObject object_create() {
    PObject obj = (PObject) malloc(sizeof(struct object));
    object_setMoveSpeed(obj,0);
    object_setFrameTime(obj,0);
    object_setCurDoing(obj,0);
    object_setTextureHeight(obj,0);
    object_setLeft(obj,false);
    object_setTextureWidth(obj,0);
    object_setObjectPositionX(obj,0);
    object_setObjectPositionY(obj,0);
    object_setObjectPositionW(obj,0);
    object_setObjectPositionH(obj,0);

    object_setObjectRectX(obj,0);
    object_setObjectRectY(obj,0);
    object_setObjectRectW(obj,0);
    object_setObjectRectH(obj,0);

    return obj;
}

PObject object_getPFrameTime(PObject object) {
    return &(object->frameTime);
}

void object_setFrameTime(PObject object, float value) {
    object->frameTime=value;
}

float object_getFrameTime(PObject object) {
    return object->frameTime;
}

void object_setLeft(PObject object, bool value) {
    object->left = value;
}

bool object_getLeft(PObject object) {
    return object->left;
}

void object_setObjectRectX(PObject object,int value) {
    object->objectRect.x = value;
}

void object_setObjectRectY(PObject object, int value) {
    object->objectRect.y = value;
}


void object_setObjectRectW(PObject object,int value) {
    object->objectRect.w = value;
}

void object_setObjectRectH(PObject object, int value) {
    object->objectRect.h = value;
}

int object_getObjectRectPX(PObject object) {
    return &(object->objectRect.x);
}

int object_getObjectRectPY(PObject object) {
    return &(object->objectRect.y);
}

int object_getObjectRectX(PObject object) {
    return (object->objectRect.x);
}

int object_getObjectRectY(PObject object) {
    return (object->objectRect.y);
}

int object_getObjectPositionX(PObject object) {
    return object->objectPosition.x;
}

int object_getObjectPositionY(PObject object) {
    return object->objectPosition.y;
}

int object_getObjectPositionH(PObject object) {
    return object->objectPosition.h;
}

int object_getObjectPositionW(PObject object) {
    return object->objectPosition.w;
}

void object_setObjectPositionX(PObject object, int value) {
    object->objectPosition.x = value;
}

void object_setObjectPositionY(PObject object, int value) {
    object->objectPosition.y = value;
}

void object_setObjectPositionH(PObject object, int value) {
    object->objectPosition.h = value;
}

void object_setObjectPositionW(PObject object, int value) {
    object->objectPosition.w = value;
}

float object_getMoveSpeed(PObject object) {
    return object->moveSpeed;
}

int object_getCurDoing(PObject object) {
    return object->curDoing;
}

int object_getTextureHeight(PObject object){
    return object->textureHeight;
}

int object_getTextureWidth(PObject object){
    return object->textureWidth;
}

SDL_Texture* object_getTexture(PObject object) {
    return object->texture;
}

SDL_Rect* object_getObjectRect(PObject object) {
    return &(object->objectRect);
}

SDL_Rect* object_getObjectPosition(PObject object) {
    return &(object->objectPosition);
}

void object_setMoveSpeed(PObject object, float value) {
    object->moveSpeed = value;
}

void object_setCurDoing(PObject object, int value){
    object->curDoing = value;
}

void object_setTextureHeight(PObject object, int value){
    object->textureHeight = value;
}

void object_setTextureWidth(PObject object, int value){
    object->textureWidth = value;
}

void object_setTexture(PObject object, SDL_Texture* value){
    object->texture = value;
}

void object_setTexturePath(PObject object, SDL_Renderer* renderer, char* path) {
    object->texture = LoadTexture(path,renderer);
}
void object_setObjectRect(PObject object, SDL_Rect value){
    object->objectRect = value;
}

void object_setObjectPosition(PObject object, SDL_Rect value){
    object->objectPosition = value;
}

void object_objectRemove(PObject object) {
    SDL_DestroyTexture(object->texture);
    free(object);
    object = NULL;
}
