#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#ifndef Sun_hpp
#define Sun_hpp

#include <stdio.h>

#endif /* Sun_hpp */


class Sun :
    public DisplayableObject,
    public Animation
{
public:
    Sun();
    Sun(const std::string& filename);
    ~Sun(){};

    void Display();
    void Update(const double& deltaTime);

private:

    void drawRec(GLfloat x, GLfloat y);

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

