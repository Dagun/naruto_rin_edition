#pragma once

#include "object.h"
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

SDL_Texture *LoadTexture(char* filePath, SDL_Renderer* renderTarget);
void swapValues(PObject *a, PObject *b);
void initializeSDL(bool *initializedSucces);
