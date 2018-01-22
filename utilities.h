#pragma once

#include "object.h"
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>

SDL_Texture *LoadTexture(char* filePath, SDL_Renderer* renderTarget);
void swapValues(PObject **a, PObject **b);
void initializeSDL(bool *initializedSucces);
