#include "event.h"
#include "camera.h"
#include "game_engine.h"
bool INT_closed;
SDL_Event e;

eventPacket event(){
    char key_down;
    INT_closed = false;
    
    int x_rel;
    int y_rel;
    eventPacket out;
    out.mouse=NONE;
    out.player_move = glm::vec3(0.0f,0.0f,0.0f);
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_KEYDOWN){
            key_down=e.key.keysym.sym;
            out.player_move += engineKeyboardEvent(key_down,true);
        }
        if(e.type==SDL_KEYUP){
            key_down=e.key.keysym.sym;
            out.player_move+= engineKeyboardEvent(key_down,false);
        }
        if(e.type==SDL_QUIT){
            INT_closed=true;
            break;
        }
        if(e.type==SDL_MOUSEMOTION){
            out.mouseMx=e.motion.xrel;
            out.mouseMy=e.motion.yrel;            
            engineMouseEvent(out.mouseMx,out.mouseMy);
        }
        if(e.type==SDL_MOUSEBUTTONDOWN){
            if(e.button.button==SDL_BUTTON_LEFT){
                out.mouse=LEFT;
            }
            if(e.button.button==SDL_BUTTON_MIDDLE){
                out.mouse=MIDDLE;
            }
            if(e.button.button==SDL_BUTTON_RIGHT){
                out.mouse=RIGHT;
            }
        }
    }
    out.thetaX=getThetaX();
    out.thetaY=getThetaY();
    return out;
}
bool isclosed(){
    return INT_closed;
}
void stopGame(){
    for(int i =0; i<10; i++){
        printf("********game stop***********\n");
    }
    INT_closed=true;
}
void resetMouse(int x, int y){
    SDL_WarpMouseInWindow(NULL,x/2,y/2);
    SDL_PeepEvents(&e,1,SDL_PEEKEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT);
    if(e.type==SDL_MOUSEMOTION)
    SDL_PollEvent(&e);
}