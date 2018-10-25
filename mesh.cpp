#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "error.h"

void Model::add(Model to_add,glm::vec3 pos){
    this->pos.reserve(this->pos.size()+to_add.pos.size());
    this->texCoord.reserve(this->texCoord.size()+to_add.texCoord.size());
    for(int i =0;i<to_add.pos.size();i++){
        this->pos.push_back(to_add.pos[i]+pos);
        this->texCoord.push_back(to_add.texCoord[i]);
    }
    int size = this->pos.size();
    for(int i =0;i<to_add.indices.size();i++){
        this->indices.push_back(to_add.indices[i]+size);
    }
}
std::vector<unsigned int> numIndicies;
std::vector<RunTimeModel> initMesh(std::vector<Model> models){

    std::vector<RunTimeModel> runmodels;
    runmodels.reserve(models.size());
    
    numIndicies.reserve(models.size());
    std::vector<GLuint> modelnum;
    modelnum.reserve(models.size());

    unsigned int numindicies;
    for(int i =0;i<models.size();i++){
        numindicies = models[i].indices.size();

        numIndicies.push_back(models[i].indices.size());
        unsigned int numindicies = models[i].indices.size();
        GLuint vertex_array_object;//becomes meshNum in runtime model
        glGenVertexArrays(1,&vertex_array_object);
        //modelnum.push_back(vertex_array_object);
        glBindVertexArray(vertex_array_object);
        glError=glGetError();

        GLuint vertex_array_buffer[numBuffers];
        glGenBuffers(numBuffers,vertex_array_buffer);

        //buffering position
        glBindBuffer(GL_ARRAY_BUFFER,vertex_array_buffer[POSITION]);
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(models[i].pos[0])*models[i].pos.size(),
            &models[i].pos[0],GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

        glError=glGetError();
        //buffering Texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER,vertex_array_buffer[TEXCOORD]);
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(models[i].texCoord[0])*models[i].texCoord.size(),
            &models[i].texCoord[0],GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

        //buffering indicies
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertex_array_buffer[INDEX]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(models[i].indices[0])*models[i].indices.size(),
        &models[i].indices[0],GL_STATIC_DRAW);

        glError=glGetError();
        runmodels.push_back(RunTimeModel(vertex_array_object,i,numindicies,vertex_array_buffer));
        
    }
    return runmodels;
}
void drawMesh(RunTimeModel model,glm::vec3 position){

    //std::cout<<model.printString();
    glBindVertexArray(model.meshNum);
     //glError=glGetError();
    glm::mat4 trans = glm::mat4(1.0f);
    
    sendTranslate(glm::translate(trans,position));
    glDrawElements(GL_TRIANGLES,model.numIndicies,GL_UNSIGNED_INT,0);

    glError=glGetError();
}
void updateMesh(std::vector<Model> models,std::vector<RunTimeModel> &to_update){
    if(to_update.size()!=models.size()){
        std::cout<<"to_update.size()!=models.size()\n";
    }
    for(int i=0;i<to_update.size();i++){
        glBindVertexArray(to_update[i].meshNum);
        glBindBuffer(GL_ARRAY_BUFFER,to_update[i].vertex_array_buffers[POSITION]);
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(models[i].pos[0])*models[i].pos.size(),
            &models[i].pos[0],GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

       

        glBindBuffer(GL_ARRAY_BUFFER,to_update[i].vertex_array_buffers[POSITION]);
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(models[i].pos[0])*models[i].pos.size(),
            &models[i].pos[0],GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

        glError=glGetError();

        

        //buffering Texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER,to_update[i].vertex_array_buffers[TEXCOORD]);
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(models[i].texCoord[0])*models[i].texCoord.size(),
            &models[i].texCoord[0],GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

        //buffering indicies
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,to_update[i].vertex_array_buffers[INDEX]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(models[i].indices[0])*models[i].indices.size(),
        &models[i].indices[0],GL_STATIC_DRAW);
        
        to_update[i].numIndicies=models[i].indices.size();
    }
}