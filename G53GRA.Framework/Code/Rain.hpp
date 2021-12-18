#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#ifndef Rain_hpp
#define Rain_hpp

#include <stdio.h>

#endif /* Rain_hpp */


class Rain :
    public DisplayableObject,
    public Animation
{
public:
    Rain();
    Rain(const std::string& filename);
    ~Rain(){};

    void Display();
    void Update(const double& deltaTime);

private:

    void drawRain(GLfloat x, GLfloat y, GLfloat z);
    void drawPlane(GLfloat size);
    void drawRains(GLfloat position[][3], int n);
    void drawRec(GLfloat x, GLfloat y);
    void drawTriangle(float x0, float y0, float z0,
                      float x1, float y1, float z1,
                      float x2, float y2, float z2);

    int keyframe;               // variable to track which keyframe we are on
    float animateTime;          // variable to store the current time the animation has run for
    float animateRotation;      // variable to track the current amount of rotation steps
    float animateTranslation;   // variable to track the current amount of translation steps
    float interpA;              // variable to hold what the first keyframe angle is
    float interpB;              // variable to hold what the second keyframe angle is
    float interpTime;           // variable to track how long the keyframe lasts i.e. how long do we have
                                // to move from interpA to interpB
    
    GLint texID;
};

