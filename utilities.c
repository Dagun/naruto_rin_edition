#include "utilities.h"

extern int height;
extern int width;

int randomNumber(int nr_min, int nr_max) {
    static bool initialized = false;
    if(!initialized) {
        srand(time(NULL));
    }
    return rand() % nr_max + nr_min;
}

SDL_Texture *LoadTexture(char* filePath, SDL_Renderer* renderTarget) {
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(filePath);
    if(surface == NULL) {
        printf("Unable to load image: %s\n",SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderTarget,surface);
    if(texture == NULL) {
        printf("Unable to create texture from surface: %s\n",SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    return texture;
}
