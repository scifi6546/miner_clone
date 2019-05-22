#include "game_engine.h"
#include "display.h"
#include "render_manager.h"
#include "mesh.h"
#include "event.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"
#include "error.h"
unsigned int frameBufferFBO;
unsigned int frameBufferTex;//depth map texture
unsigned int mainBufferFBO;

render_target *gameWorld_ptr;
GLenum error;

Model buffer=Model(
    {glm::vec3(-1.0,-1.0,0.0),glm::vec3(1.0,-1.0,0.0),
        glm::vec3(1.0,1.0,0.0),glm::vec3(1.0,-1.0,1.0)},
    {glm::vec2(-1.0,-1.0),glm::vec2(1.0,-1.0),
        glm::vec2(1.0,1.0),glm::vec2(1.0,-1.0)},{0,1,2,0,3,2},
    {glm::vec3(0.0,0.0,-1.0),glm::vec3(0.0,0.0,-1.0),
        glm::vec3(0.0,0.0,-1.0),glm::vec3(0.0,0.0,-1.0)});
RunTimeModel buffer_model;
void rManager::makeFBO(render_target &in){
    
    getError();
    glGenFramebuffers(1,&in.bufer_object.FBO_OJECT);
    printf("in_fbo_object: %i",in.bufer_object.FBO_OJECT);
    glBindFramebuffer(GL_FRAMEBUFFER,in.bufer_object.FBO_OJECT);
    in.bufer_object.attTexture=genTextureEmp();
    getError();
    /*
    glGenTextures(1,&in.bufer_object.COLOR_MAP);
    glBindTexture(GL_TEXTURE_2D,in.bufer_object.COLOR_MAP);
    getError();
    //Creating Color Map
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    */
    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
    //    GL_TEXTURE_2D,in.bufer_object.COLOR_MAP,0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,in.bufer_object.attTexture.color_texture,0);
    getError();

    //creating depth map
    //glGenTextures(1,&in.bufer_object.DEPTH_MAP);
    //glBindTexture(GL_TEXTURE_2D,in.bufer_object.DEPTH_MAP);

    //glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,800,600,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);
    //getError();
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,in.bufer_object.attTexture.depth_texture,0);
    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
    //    GL_TEXTURE_2D,in.bufer_object.DEPTH_MAP,0);
    
    //glBindTexture(GL_TEXTURE_2D,0);
    getError();

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    getError();
    
}
//todo check if gameWorld is active
void sendAmbientInfo(glm::vec3 color,GLfloat intensity,
    glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color){
        getError();
        sendVec3("ambient_color",color,*gameWorld_ptr);
        getError();
        sendGLfloat("ambient_intensity",intensity,*gameWorld_ptr);
        getError();
        sendVec3("sun_pos",sun_pos,*gameWorld_ptr);
        getError();
        sendGLfloat("sun_intensity",sun_intensity,*gameWorld_ptr);
        getError();
        sendVec3("sun_color",sun_color,*gameWorld_ptr);
        getError();
}
void rManager::bindFBO(render_target in){

    getError();
    if(error!=0){
        printf("glError (before binding)!!!\n\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER,in.bufer_object.FBO_OJECT);//Error on this line!
    //printf("FBO OBJECT: %i\n",in.FBO_OJECT);
    getError();
    if(error!=0){
        printf("glError (after binding)!!!\n\n");
    }
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
        printf("framebuffer incomplete error!\nerror!\n");
    //printf("bound buffer (after binding): %i ",in);
}
render_target gameWorld;//game world will be rendered to here
render_target bufferWorld;//Buffer shader
void initRender(){
    //unsigned int *inFBO = new unsigned int[2];
    //glGenFramebuffers(2,inFBO);
    getError();
    initDisplay(display_width,display_height,"temp_title");
    gameWorld_ptr=&gameWorld;
    

    //shaderInit();
    
    getError();
    createShaderT({"shaders/shader.vs","shaders/shader.fs"},gameWorld);
    createShaderT({"shaders/buffer_shader.vs","shaders/buffer_shader.fs"},bufferWorld);
    getError();
    useShader(gameWorld);
    getError();
    initCam(60.0,display_width,display_height,.01,500);
    getError();
    rManager::makeFBO(gameWorld);
    std::vector<RunTimeModel> in = initMesh({buffer});
    buffer_model=in[0];
    getError();
    
}
void drawFrame(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    //rManager::bindFBO(gameWorld);
    //useGameShader();
    getError();
  
    useShader(gameWorld);
    //clearDisplay(0.0,.1,.6,1.0);
    
    //drawMesh(buffer_model,glm::vec3(1.0,100.0,0.0));
    draw();
    //glGetIntegerv(GL_FRAMEBUFFER_BINDING,&in);
    //printf("bound buffer (after rendering): %i\n",in);
    
    getError();
    if(error)
        printf("ERROR!\n\n\n");
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    //useShader(bufferWorld);
    //useFrameCam();
    //bindTexture(gameWorld.bufer_object.attTexture,gameWorld,"diffuse");
    
    //drawMeshBuffer(buffer_model,glm::vec3(1.0,100.0,0.0));
    resetMouse(getWidth(),getHeight());
    updateDisplay();
    error=glGetError();
}
void sendCameraPos(glm::vec3 position){
    translateCam(position);
}
void sendCameraLook(float thetax,float thetay){
    rotate_cam(thetax,thetay);
}