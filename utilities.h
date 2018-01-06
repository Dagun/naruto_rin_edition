#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "SDL.h"

int randomNumber(int nr_min, int nr_max);
SDL_Texture *LoadTexture(char* filePath, SDL_Renderer* renderTarget);
