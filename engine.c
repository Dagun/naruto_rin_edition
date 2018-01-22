#include "engine.h"

extern const int width;
extern const int rin_heightTolerance;

void engine_gravity(float *frameTime, float deltaTime, PPlayer ply, PObject obj) { *frameTime = *frameTime + deltaTime;
  if ( *frameTime > 0.01) {
    if (engine_collisionGround(ply, obj)) {
      int tmp = player_getPlayerPositionY(ply) + 5;
      player_setPlayerPositionY(ply, tmp); *frameTime = 0;
    }
  }
}

void engine_outSideMap(PPlayer ply) {
  if (player_getPlayerPositionX(ply) < -20) {
    player_setPlayerPositionX(ply, width);
  } else if (player_getPlayerPositionX(ply) > width) {
    player_setPlayerPositionX(ply, -20);
  }
}

int engine_collisionGround(PPlayer ply, PObject obj) {
  if (player_getPlayerPositionY(ply) + rin_heightTolerance <= object_getObjectPositionY(obj)) {
    if (player_getPlayerPositionX(ply) + rin_heightTolerance >= object_getObjectPositionX(obj) && player_getPlayerPositionX(ply) - rin_heightTolerance <= object_getTextureWidth(obj)) {
      if (player_getPlayerPositionY(ply) + rin_heightTolerance >= object_getObjectPositionY(obj)) {
        player_setOnGround(ply, true);
        return 0;
      }
    }
  } else {
    if (player_getDead(ply) == false)
      player_setHealth(ply, player_getHealth(ply) - 1);
  }
  player_setOnGround(ply, false);
  return 1;
}

int engine_playerCollision(PPlayer ply, PPlayer ply2) {
  if (player_getPlayerPositionX(ply) > player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply) < player_getPlayerPositionX(ply2) + rin_heightTolerance) {
    return 2;
  } else if (player_getPlayerPositionX(ply) + rin_heightTolerance > player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply) < player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply) + rin_heightTolerance > player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply2) + rin_heightTolerance > player_getPlayerPositionX(ply)) {
    return 1;
  }
  return 0;
}
