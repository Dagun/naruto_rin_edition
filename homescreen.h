#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif
#include "utilities.h"
#include "animation.h"
#include "player.h"
#include "engine.h"
#include "object.h"
#include "homescreen.h"

typedef struct homeScreen PHomeScreen;

void homeScreen_start();
