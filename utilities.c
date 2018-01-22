#include "utilities.h"

extern int height;
extern int width;

SDL_Texture *LoadTexture(char *filePath, SDL_Renderer *renderTarget) {
  SDL_Texture *texture = NULL;
  SDL_Surface *surface = IMG_Load(filePath);
  if (surface == NULL) {
    printf("Unable to load image: %s\n", SDL_GetError());
    return NULL;
  }
  texture = SDL_CreateTextureFromSurface(renderTarget, surface);
  if (texture == NULL) {
    printf("Unable to create texture from surface: %s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    return NULL;
  }
  SDL_FreeSurface(surface);
  return texture;
}

void swapValues(PObject **a, PObject **b) {
  PObject *tmp = *a; *a = *b; *b = tmp;
  tmp = NULL;
}

void initializeSDL(bool *initializedSucces) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());*initializedSucces = false;
  }

  if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());*initializedSucces = false;
  }
  int imgFlag = IMG_INIT_JPG | IMG_INIT_PNG;
  if (!(IMG_Init(imgFlag) & imgFlag)) {
    printf("Unable to initialize SDL Image: %s\n", IMG_GetError()); *initializedSucces = false;
  }
}
