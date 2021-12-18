#include "Rain.hpp"

#include <iostream>

#include <cmath>

#define PI 3.14

#include <stdio.h>
#include <stdlib.h>

Rain::Rain() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Rain::Rain(const std::string& filename) : Rain()
{
    texID = Scene::GetTexture(filename);
}

/// Update the Rains position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Rain::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
    // animateRotation = animateTime*10;//	animateRotation += static_cast<float>(deltaTime); // if you uncomment this code, it will rotate
    
}

void Rain::drawRec(GLfloat x, GLfloat y){
    glEnable(GL_TEXTURE_2D);
    // This function draws a rectangle.
    
    glColor4f(1, 1, 1, 0.5);
    // Tell openGL which texture buffer to use
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, y, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-x, 0, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, 0, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, 0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Rain::drawRain(GLfloat x, GLfloat y, GLfloat z){
    // This function draws a Rain with texture.
    glPushMatrix();
    glTranslatef(x, y, z);
    for(int i=0;i<6;i++){
        glRotatef(360/6, 0, 1, 0);
        drawRec(0.02, 0.6);
    }
    glPopMatrix();
}

void Rain::drawRains(GLfloat position[][3], int n){
    // this function draws many Rains. input an array containing the coor info for each Rain, and how many Rains are there.
    for(int i=0; i<n; i++){
        drawRain(position[i][0], position[i][1], position[i][2]);
    }
}

void Rain::Display(void){
    // this function displays the Rains.
    glPushMatrix();
    glRotatef(animateRotation,0,1,0);
    glTranslatef(0, -animateTime*5, 0);
    
    // init the Rains' position here. add random biases to avoid to be too neat
    GLfloat x[2][3] = {
        {0, 10, 0},
        {3, 10, 0}
    };
    drawRains(x, 2); // 11 Rains in total
    
    glPopMatrix();
    
}
