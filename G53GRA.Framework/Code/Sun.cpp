#include "Sun.hpp"
#include <iostream>

#include <cmath>

#define PI 3.14

#include <stdio.h>
#include <stdlib.h>

// 随机生成一个雨，速度、位置、随机，大小固定。

Sun::Sun() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Sun::Sun(const std::string& filename) : Sun()
{
    texID = Scene::GetTexture(filename);
}

/// Update the Suns position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Sun::Update(const double& deltaTime)
{
    // update the time and rotation steps
    animateTime += static_cast<float>(deltaTime);
    animateRotation = animateTime*10;//    animateRotation += static_cast<float>(deltaTime); // if you uncomment this code, it will rotate
    
}

void Sun::drawRec(GLfloat x, GLfloat y){
    // This function draws a rectangle.
    
    glColor3f(0.8f, 0.8f, 0.0f);
    glutSolidSphere(2, 10, 10);
    // Tell openGL which texture buffer to use
    /*
     
     glEnable(GL_TEXTURE_2D);
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
     */
}

void Sun::Display(void){
    // this function displays the Suns.
    glPushMatrix();
    glRotatef(animateRotation*0.04, 0, 0, 1);
    glTranslatef(30, 50, -30);
    //glTranslatef(-30, -20, -30);
    drawRec(1, 1);
    
    glPopMatrix();
    
}
