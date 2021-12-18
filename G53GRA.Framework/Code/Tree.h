#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

/*
This is a class that should dispaly our Tree with they rough rigid body
transform between our key frames
Here is a more complex example of the effects that can be achieved:
http://www.youtube.com/watch?v=cdtHSyfcSDs
*/

class Tree :
	public DisplayableObject,
	public Animation
{
public:
	Tree();
    Tree(const std::string& filename);
	~Tree(){};

	void Display();
	void Update(const double& deltaTime);

private:
    void drawRec(GLfloat x, GLfloat y);  // function to draw a rectangle
    void drawTree(GLfloat x, GLfloat y, GLfloat z);  // function to draw a tree
    void drawTrees(GLfloat x[][3], int n);  // function to draw many trees

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

