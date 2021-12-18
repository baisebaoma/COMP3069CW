#include "Sky.hpp"

#include <iostream>

#include <cmath>

// TODO: 现在是全写在Sky里，到时候得分开成各个东西。（refactor）

#include <stdio.h>
#include <stdlib.h>

// MAKE SURE WE INITIALISE OUR VARIABLES
Sky::Sky() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Sky::Sky(const std::string& filename) : Sky()
{
    texID = Scene::GetTexture(filename);
}

/// Update the Skys position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Sky::Update(const double& deltaTime)
{
    // update the time and rotation steps
    animateTime += static_cast<float>(deltaTime);
    // animateRotation = animateTime*10;//    animateRotation += static_cast<float>(deltaTime);
}

void Sky::drawPlane(GLfloat R, GLfloat G, GLfloat B, GLfloat size){
    glColor3f(R, G, B);
    
    glEnable(GL_TEXTURE_2D);

    // Enable setting the colour of the material the cube is made from
    // as well as the material for blending.
    // glEnable(GL_COLOR_MATERIAL);

    // Tell openGL which texture buffer to use
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1*size, 0, -1*size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1*size, 0, 1*size);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(size, 0, size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, 0, -1*size);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Sky::Display(void){

    glPushMatrix();
    glRotatef(animateRotation,0,1,0);
    
    // Sky
    glPushMatrix();
    glTranslatef(5, 0, 5);
    drawPlane(0.7f, 0.7f, 0.7f, 20);
    glPopMatrix();

    glPopMatrix();
}
