#include "Tree.h"

#include <iostream>

#include <cmath>

#define PI 3.14

#include <stdio.h>
#include <stdlib.h>

Tree::Tree() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

Tree::Tree(const std::string& filename) : Tree()
{
    texID = Scene::GetTexture(filename);
}

/// Update the Trees position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Tree::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
    // animateRotation = animateTime*10;//	animateRotation += static_cast<float>(deltaTime); // if you uncomment this code, it will rotate
    
}

void Tree::drawRec(GLfloat x, GLfloat y){
    glEnable(GL_TEXTURE_2D);
    // This function draws a rectangle.
    
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

void Tree::drawTree(GLfloat x, GLfloat y, GLfloat z){
    // This function draws a tree with texture.
    glColor3f(0, 1, 0);
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(0.4*sin(animateTime)+6*sin(animateTime*1.3), 0, 1, 0);
    glDisable(GL_DEPTH_TEST);  // [IMPORTANT] disable GL_DEPTH_TEST to avoid shelting. see the report.
    for(int i=0;i<360;i+=360/10){  // 10 is the best amount to balance transparency and visualbility
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        drawRec(4, 16);
        glPopMatrix();
    }
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    
    glColor3f(1, 1, 1);
    
}

void Tree::drawTrees(GLfloat position[][3], int n){
    // this function draws many trees. input an array containing the coor info for each tree, and how many trees are there.
    for(int i=0; i<n; i++){
        drawTree(position[i][0], position[i][1], position[i][2]);
    }
}

void Tree::Display(void){
    // this function displays the trees.
    glPushMatrix();
    // glRotatef(animateRotation,0,1,0);
    
    // init the trees' position here. add random biases to avoid to be too neat
    GLfloat x[20][3] = {
        {0, 0, 0},
        
        {10, 0, 0},
        {10*float(cos(PI/6)-1), 0, 10*float(sin(PI/6))+0.3f},
        {11*float(cos(-PI/6)+0.4f), 0, 9*float(sin(-PI/6))-0.1f},
        {9*float(cos(PI/3)+0.8f), 0, 12*float(sin(PI/3))-0.4f},
        
        {14, 0, 0},
        {13*float(cos(PI/6))-0.4f, 0, 15*float(sin(PI/6))+0.5f},
        {14*float(cos(-PI/6)-0.3f), 0, 15*float(sin(-PI/6))-0.4f},
        
        {18, 0, 0},
        {0, 0, -4},
        
        {3, 0, 2},
    };
    drawTrees(x, 11); // 11 trees in total
    glPopMatrix();
    
}
