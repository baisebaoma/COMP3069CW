#include "Grass.hpp"

#include <iostream>

#include <cmath>

#include <stdio.h>
#include <stdlib.h>

// MAKE SURE WE INITIALISE OUR VARIABLES
Grass::Grass() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Grass::Grass(const std::string& filename, float random_position[][2]) : Grass()
{
    texID = Scene::GetTexture(filename);
    random_position = random_position;
}

/// Update the Grasss position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Grass::Update(const double& deltaTime)
{
    // update the time and rotation steps
    animateTime += static_cast<float>(deltaTime);
    // animateRotation = animateTime*10;//    animateRotation += static_cast<float>(deltaTime);
}

void Grass::drawRec(GLfloat x, GLfloat y){
    glEnable(GL_TEXTURE_2D);
    glColor3f(0, 1, 0);

    // Enable setting the colour of the material the cube is made from
    // as well as the material for blending.
    // glEnable(GL_COLOR_MATERIAL);

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

void Grass::Display(void){
    
    glColor3f(0, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(animateRotation,0,1,0);
    
    glDisable(GL_DEPTH_TEST);
    
    for(int x=0;x<15;x++){
        for(int z=0;z<10;z++){
            // Grass
            glPushMatrix();
            glTranslatef(x, 0, z);
            glRotatef(0.4*sin((animateTime-2*z+3*x)*(2-x))+1*sin(animateTime*3), 0, 0, 1);
            glRotatef(3*sin((animateTime+2*z-3*x)*(5+z))+2*sin(animateTime*13), 1, 0, 0);
            for(int i=0;i<360;i+=360/6){
                glPushMatrix();
                glRotatef(i, 0, 1, 0);
                drawRec(0.8, 2);
                glPopMatrix();
            }
            glPopMatrix();
        }
    }
    
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    
}
