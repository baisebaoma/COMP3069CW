#pragma once

#ifdef _WIN32
#include <GL/glut.h>
#include <Windows.h>
#else
#include <GLUT/glut.h>
#endif

#include "../Interface/Input.h"
/**
* This class implements the base Camera functionality. It controls the position and view direction
* of the camera in your {@link Scene}. You may add functionality by creating a new class that inherits
* <code>Camera</code>, e.g. {@code class MyCamera : public Camera}. You should avoid editting this class directly.
* <p>
* Note that {@code Camera} extends the virtual class {@link Input}, so will be passed key and mouse input by the window
* @author wil
*/
class Camera : public Input
{
public:
	/** Constructor for {@link Camera} to set up viewing properties in rendering window */
	Camera();
	virtual ~Camera(){};

	// These functions can be called to get the position/view direction/camera axis of the camera in world space
	void GetEyePosition(float &x, float &y, float &z) const;
	void GetViewDirection(float &x, float &y, float &z) const;
	void GetForwardVector(float &x, float &y, float &z) const;
	void GetRightVector(float &x, float &y, float &z) const;
	void GetUpVector(float &x, float &y, float &z) const;

	/**
	* Update the position of the camera and look-at vectors based on keyboard input.
	* @param deltaTime change in time since previous call (unused)
	*/
	virtual void Update(const double& deltaTime);

	/**
	* Resets {@link Camera} vectors to default values. Sets position of camera at (0,0) in x,y-plane
	* and puts z-position at {@code 0.5*height/tan(pi/6)} which puts the coordinate width and height of window
	* into view (if projection is in perspective view, and both {@code fovy = 60}&deg; and {@code aspect =  width/height})
	* <p>
	* {@code width} and {@code height} refer to the window size of {@code Scene} {@link #parent}.
	*/
	virtual void Reset();
	/** Sets the window viewport of the scene */
	virtual void SetViewport();

	/**
	* Captures input from {@code wasd}-keys used for camera movement.
	* <p>
	* Spacebar {@linkplain #reset() reset}s the camera.
	*/
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y){}; // unused at present

	/**
	* Captures button click. Sets button to 0 if last mouse button is released.
	* Saves current position of mouse at click.
	* @see #HandleMouseDrag(int, int)
	*/
	void HandleMouse(int button, int state, int x, int y);

	/**
	* Called when mouse is moved (while a button is pressed down). Functionality currently only for <b>LEFT</b> mouse click.
	* <p>
	* Calculates difference in mouse position since last call and adjusts camera {@link #view} accordingly. Sensitivity is fixed at 0.01f.
	* @see #HandleMouse(int, int, int, int)
	*/
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y){}; // unused at preset

	/**
	* Called by {@link Scene} to position camera.
	* <p>
	* Sets up position ({@link #eye}), look at ({@code cen=} {@link #eye} {@code +} {@link #view}) and
	* up vector ({@link #up}) and updates Scene viewing.
	* @see #Update(float)
	* @see #Reset()
	*/
	virtual void SetupCamera();

private:
	/**
	* Vectors containing eye coordinates, i.e. the position of the camera.
	* <p>
	* Position in space that the camera is looking at equals {@code eye+}{@link #view}.
	*/
	float eyePosition[3];
	/**
	* The vector along which the camera are looking.
	* <p>
	* Position in space that the camera is looking at equals {@link #eye}{@code +view}.
	*/
	float vd[3];
	/** Vector representing forward orthogonal axes of your {@link Camera} space. */
	float forward[3];
	/** Vector representing right orthogonal axes of your {@link Camera} space. */
	float right[3];
	/** Vector representing upward orthogonal axes of your {@link Camera} space. */
	float up[3];

	/**
	 * Member variable used to track when a key is pressed between frames
	 * so that we can do an update in the Update() function rather than HandleKey
	 * function to obtain smooth motion */
	int wKey, sKey, aKey, dKey;

	/** Current rendering window dimensions */
	int windowWidth, windowHeight;

	/** Variable to remember mouse click */
	int currentButton;
	/** Previous mouse coordinates */
	GLint mouseX, mouseY;
};