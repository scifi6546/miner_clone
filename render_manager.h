#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "render_target.h"
const int display_height = 800;
const int display_width = 1000;
/*
This will be used to render a model
*/
struct rModel{
    unsigned int ModelNum;
};
//public functions
//initilizes render manager
void initRender();
//draws frame called every frame draw
void drawFrame();
/*
NOT TESTED
sends the camera position (world coordinates) to the rendering engine 
*/
void sendCameraPos(glm::vec3 position);

/*
NOT TESTED
Sends the camera look to the rendering engine
*/
void sendCameraLook(float thetax,float thetay);
/*
NOT IMPLEMENTED OR TESTED
Sends world color data to the gpu
*/
void sendAmbientInfo(glm::vec3 color,GLfloat intensity,
    glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color);
//private functions
namespace rManager{
    const unsigned int shadow_width = 1024, shadow_height=1024;
    //initilizes frame buffer object and modifies in
    void makeFBO(render_target &in);
    //binds a frame buffer object struct
    void bindFBO(render_target in);
}
#endif