#include <glm/glm.hpp>
#include "block.h"
#ifndef PHYSICS_H
#define PHYSICS_H
struct intVec2{
    int x;
    int y;
};
struct intVec3{
    int x;
    int y;
    int z;
};
namespace physics{
    const float slideConst = 0.7f;
    const float collideDist = 0.4f;//distance of collision
    const float playerMoveSpeed = 0.2f;
    const glm::vec3 gravity = glm::vec3(0.0f,-0.02f,0.0f);
    glm::vec3 runFrame(glm::vec3 player_pos, 
        glm::vec3 player_v, World *gameWorld,float deltaT); 
    const int look_dist = 4;
    intVec3 getLookPos(glm::vec3 player_pos,float thetaX,float thetaY);
    
} // name physics

#endif