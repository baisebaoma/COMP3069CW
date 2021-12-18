#include "Ground.hpp"

#include <iostream>

#include <cmath>

#include <stdio.h>
#include <stdlib.h>


// MAKE SURE WE INITIALISE OUR VARIABLES
Ground::Ground() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Ground::Ground(const std::string& filename) : Ground()
{
    texID = Scene::GetTexture(filename);
}

/// Update the Grounds position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Ground::Update(const double& deltaTime)
{
    // update the time and rotation steps
    animateTime += static_cast<float>(deltaTime);
    // animateRotation = animateTime*10;//    animateRotation += static_cast<float>(deltaTime);
}

void Ground::drawPlane(GLfloat R, GLfloat G, GLfloat B, GLfloat size){
    glColor3f(R, G, B);
    
    glEnable(GL_TEXTURE_2D);

    // Enable setting the colour of the material the cube is made from
    // as well as the material for blending.
    // glEnable(GL_COLOR_MATERIAL);

    // Tell openGL which texture buffer to use
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0, 0, 1*size);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(size, 0, size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, 0, 0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Ground::drawCoor(){
    // draw coordinates
    glLineWidth(3.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f); // Red x
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    
    glColor3f(0.0, 1.0, 0.0); // Green y
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();
    
    glColor3f(0.0, 0.0, 1.0); // Blue z
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
    
}

void Ground::Display(void){

    glPushMatrix();
    glRotatef(animateRotation,0,1,0);
    
    // ground
    glPushMatrix();
    glTranslatef(-5, 0, -10);
    drawPlane(0.0f, 0.4f, 0.0f, 25);
    glPopMatrix();
    
    glPushMatrix();
    drawCoor();
    glPopMatrix();

    glPopMatrix();
}
