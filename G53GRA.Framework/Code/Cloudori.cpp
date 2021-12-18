#include "Cloud.hpp"

#include <iostream>

#include <cmath>

#include <stdio.h>
#include <stdlib.h>


// ------------------------------------------------------


// MAKE SURE WE INITIALISE OUR VARIABLES
Cloud::Cloud() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Cloud::Cloud(const std::string& filename) : Cloud()
{
    texID = Scene::GetTexture(filename);
}

/// Update the Clouds position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Cloud::Update(const double& deltaTime)
{
    // update the time and rotation steps
    animateTime += static_cast<float>(deltaTime);
    // animateRotation = animateTime*10;//    animateRotation += static_cast<float>(deltaTime);
}

void Cloud::drawPlane(GLfloat size){
    glColor3f(0, 1, 0);
    
    glEnable(GL_TEXTURE_2D);

    // Enable setting the colour of the material the cube is made from
    // as well as the material for blending.
    // glEnable(GL_COLOR_MATERIAL);

    // Tell openGL which texture buffer to use
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, 0, -1*size);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(size, 0, size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1*size, 0, 1*size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1*size, 0, -1*size);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Cloud::Display(void){

    glPushMatrix();
    glRotatef(animateRotation,0,1,0);
    
    // Cloud
    glPushMatrix();
    glTranslatef(0, 5, 0);
    drawPlane(10);
    glPopMatrix();

    glPopMatrix();
    
}
