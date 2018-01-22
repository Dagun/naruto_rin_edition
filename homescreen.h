#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "utilities.h"
#include "animation.h"
#include "player.h"
#include "engine.h"
#include "object.h"
#include "homescreen.h"

typedef struct homeScreen PHomeScreen;

void homeScreen_start();
