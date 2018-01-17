#include "engine.h"

extern const int rin_heightTolerance;
extern const int outSideMapTolerance;
extern const int width;

void engine_gravity(float *frameTime, float deltaTime, PPlayer ply, PObject obj) {
    *frameTime = *frameTime + deltaTime;
    if(*frameTime > 0.01) {
        if(engine_collisionGround(ply,obj)) {
            int tmp = player_getPlayerPositionY(ply)+5;
            player_setPlayerPositionY(ply,tmp);
            *frameTime = 0;
        }
    }
}

void engine_outSideMap(PPlayer ply) {
    if(player_getPlayerPositionX(ply)<-20) {
        player_setPlayerPositionX(ply,width);
    } else if(player_getPlayerPositionX(ply)>width) {
        player_setPlayerPositionX(ply,-20);
    }
}

int engine_collisionGround(PPlayer ply, PObject obj) {
    if(player_getPlayerPositionY(ply)+rin_heightTolerance <= object_getObjectPositionY(obj)) {
        if(player_getPlayerPositionX(ply)+rin_heightTolerance >= object_getObjectPositionX(obj)&& player_getPlayerPositionX(ply)-rin_heightTolerance <= object_getTextureWidth(obj)) {
            if(player_getPlayerPositionY(ply)+rin_heightTolerance >= object_getObjectPositionY(obj)) {
                player_setOnGround(ply,true);
                return 0;
            }
        }
    }
    player_setOnGround(ply,false);
    return 1;
}

void engine_clouds(PObject obj) {
    if(object_getFrameTime(obj)> 14) {
        object_setFrameTime(obj,0);
    }
    float tmpFrameTime = object_getFrameTime(obj);
    switch((int) tmpFrameTime) {
    case 1: object_setObjectPositionX(obj,-500); break;
     case 2:object_setObjectPositionX(obj,-200); break;
    case 3: object_setObjectPositionX(obj,0); break;
    case 4: object_setObjectPositionX(obj,250); break;
    case 5: object_setObjectPositionX(obj,450); break;
    case 6: object_setObjectPositionX(obj,500); break;
    case 7: object_setObjectPositionX(obj,700); break;
    case 8: object_setObjectPositionX(obj,900); break;
    case 9: object_setObjectPositionX(obj,1100); break;
    case 10: object_setObjectPositionX(obj,1300); break;
    case 11:  object_setObjectPositionX(obj,1500); break;
    case 12: object_setObjectPositionX(obj,1800); break;
    case 13:  object_setObjectPositionX(obj,2000); break;
    case 14: object_setObjectPositionX(obj,2300); break;
    }
}

int engine_playerCollision(PPlayer ply, PPlayer ply2) {
    if(player_getPlayerPositionX(ply) > player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply) < player_getPlayerPositionX(ply2)+rin_heightTolerance) {
        return 2;
    } else if(player_getPlayerPositionX(ply)+rin_heightTolerance > player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply) < player_getPlayerPosition(ply2) && player_getPlayerPosition(ply)+rin_heightTolerance > player_getPlayerPositionX(ply2) && player_getPlayerPositionX(ply2)+rin_heightTolerance > player_getPlayerPositionX(ply)) {
        return 1;
    }
    return 0;
}
