#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#ifndef Ground_hpp
#define Ground_hpp

#include <stdio.h>

#endif /* Ground_hpp */


class Ground :
    public DisplayableObject,
    public Animation
{
public:
    Ground();
    Ground(const std::string& filename);
    ~Ground(){};

    void Display();
    void Update(const double& deltaTime);

private:

    void drawGround();
    void drawMount(GLfloat x, GLfloat y, GLfloat z);
    void drawCoor();
    void drawPlane(GLfloat R, GLfloat G, GLfloat B, GLfloat size);

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

