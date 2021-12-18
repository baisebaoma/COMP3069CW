#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#ifndef Cloud_hpp
#define Cloud_hpp

#include <stdio.h>

#endif /* Cloud_hpp */


class Cloud :
    public DisplayableObject,
    public Animation
{
public:
    Cloud();
    Cloud(const std::string& filename);
    ~Cloud(){};

    void Display();
    void Update(const double& deltaTime);

private:
    void drawRec(GLfloat x, GLfloat y);
    void drawCloud(GLfloat x, GLfloat y, GLfloat z);
    void drawPlane(GLfloat size);
    void drawClouds(GLfloat position[][3], int n);
    
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

