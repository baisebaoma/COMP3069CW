#include "Cloud.hpp"

#include <iostream>

#include <cmath>

#define PI 3.14
#define GRAVITY 9.8

#include <stdio.h>
#include <stdlib.h>

Cloud::Cloud() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Cloud::Cloud(const std::string& filename) : Cloud()
{
    texID = Scene::GetTexture(filename);
}


/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Cloud::Update(const double& deltaTime)
{
    // update the time and rotation steps
    animateTime += static_cast<float>(deltaTime);
    animateRotation += static_cast<float>(deltaTime);
    animateTranslation = 4.0f * -GRAVITY * (animateTime - 1.0f) + 0.5f *(animateTime - 1.0f) * (animateTime - 1.0f) * 4.0f * GRAVITY;
}

void Cloud::drawRec(GLfloat x, GLfloat y){
    // This function draws a rectangle.
    glEnable(GL_TEXTURE_2D);
    
    glColor3f(1, 1, 1);
    // Tell openGL which texture buffer to use
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, 0, y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-x, 0, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, 0, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, 0, y);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Cloud::drawCloud(GLfloat x, GLfloat y, GLfloat z){
    // This function draws a Cloud with texture.
    
    glPushMatrix();
    glTranslatef(x, y, z);
    drawRec(6, 6);
    glPopMatrix();
    
}

void Cloud::drawClouds(GLfloat position[][3], int n){
    // this function draws many Clouds. input an array containing the coor info for each Cloud, and how many Clouds are there.
    for(int i=0; i<n; i++){
        drawCloud(position[i][0], position[i][1], position[i][2]);
    }
}

void Cloud::Display(void){
    // this function displays the Clouds.
    glPushMatrix();
    glRotatef(animateRotation,0,1,0);
    
    // init the Clouds' position here. add random biases to avoid to be too neat
    GLfloat x[5][3] = {
        {0, 10, 12},
        
        {10, 12, -6},
        {14*float(cos(PI/6)-1), 14, 10*float(sin(PI/6))+0.3f},
        {11*float(cos(-PI/6)+0.4f), 53, 9*float(sin(-PI/6))-0.1f},
        {9*float(cos(PI/3)+0.8f), 23, 12*float(sin(PI/3))-0.4f}
    };
    drawClouds(x, 5); // 5 Clouds in total
    glPopMatrix();
}
