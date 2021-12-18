#pragma once

#include "Scene.h"
/**
* Virtual class to be inherited by all objects to be displayed in Scene
* <p>
* Contains purely virtual {@link #Display} method that must be overloaded. {@link #Display()} is called from {@link Scene}.
* @author wil
*/
class DisplayableObject
{
public:
	/**
	 * Default constructor
	 * <p> Initialises position, size and orientation to origin in World Space.
	 */
	DisplayableObject(){
		position(0.0f, 0.0f, 0.0f);
		size(1.0f);
		orientation(0.0f, 0.0f, 0.0f);
	};
	virtual ~DisplayableObject(void){};
	/**
	* Virtual method. Called from Scene parent.
	* <p>
	* Must be overloaded by your DisplayableObject subclass. Contains all rendering commands.
	*/
	virtual void Display() = 0;
	/** set World Space position */
	void position(float x, float y, float z){
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	/** set size in World Space (single value) */
	void size(float s){
		size(s, s, s);
	}
/** set size in World Space (seperate axes) */
	void size(float sx, float sy, float sz){
		scale[0] = sx;
		scale[1] = sy;
		scale[2] = sz;
	}
	/** set orientation in World Space */
	void orientation(float rx, float ry, float rz){
		rotation[0] = rx;
		rotation[1] = ry;
		rotation[2] = rz;
	}
	/** Get size in World Space */
	float* size(){
		return scale;
	}
/** Get orientation in World Space */
	float* orientation(){
		return rotation;
	}
/** Get World Space position */
	float* position(){
		return pos;
	}

protected:
	/** float[] containing World Space position coordinates */
	float pos[3];
	/** float[] containing relative World Space scaling values for x,y,z */
	float scale[3];
	/** float[] containing angles of orientation in World Space for x, y, and z axes */
	float rotation[3];
};