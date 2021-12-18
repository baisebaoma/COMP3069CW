#include "Camera.h"
#include "VectorMath.h"
#include "Scene.h"

Camera::Camera() : wKey(0), sKey(0), aKey(0), dKey(0), currentButton(0), mouseX(0), mouseY(0)
{
	Reset();
}

void Camera::Reset(){
	// set the camera position to start at (0,0,0)
//	eyePosition[0] = 16.5f;
//	eyePosition[1] = 1.0f;
//    eyePosition[2] = 11.8f;
    eyePosition[0] = 4.0f;
    eyePosition[1] = 1.0f;
    eyePosition[2] = 11.0f;
    

	// set the view direction vector of the camera to be (0,0,-1)
	vd[0] = 3.0f;
	vd[1] = 5.0f;
	vd[2] = -10.0f;

	// set the planar forward direction vector of the camera to be (0,0,-1)
	forward[0] = 0.0f;
	forward[1] = 0.0f;
	forward[2] = -1.0f;

	// set the right vector to point along the x axis
	right[0] = 1.0f;
	right[1] = 0.0f;
	right[2] = 0.0f;

	// set the up vector of the camera to be up the y axis
	up[0] = 0.0f;
	up[1] = 1.0f;
	up[2] = 0.0f;
}

void Camera::SetViewport()
{
	glViewport(static_cast<GLint>(0), static_cast<GLint>(0), static_cast<GLsizei>(Scene::GetWindowWidth()), static_cast<GLsizei>(Scene::GetWindowHeight()));
}

void Camera::SetupCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2],
			  eyePosition[0] + vd[0], eyePosition[1] + vd[1], eyePosition[2] + vd[2],
			  up[0], up[1], up[2]);
}

void Camera::Update(const double& deltaTime)
{
	float speed = 0.3f;

	if (aKey)
		sub(eyePosition, right, speed);

	if (dKey)
		add(eyePosition, right, speed);

	if (wKey)
		add(eyePosition, forward, speed);

	if (sKey)
		sub(eyePosition, forward, speed);

	SetupCamera();
}

void Camera::GetEyePosition(float &x, float &y, float &z) const
{
	x = eyePosition[0];
	y = eyePosition[1];
	z = eyePosition[2];
}

void Camera::GetViewDirection(float &x, float &y, float &z) const
{
	x = vd[0];
	y = vd[1];
	z = vd[2];
}

void Camera::GetForwardVector(float &x, float &y, float &z) const
{
	x = forward[0];
	y = forward[1];
	z = forward[2];
}

void Camera::GetRightVector(float &x, float &y, float &z) const
{
	x = right[0];
	y = right[1];
	z = right[2];
}

void Camera::GetUpVector(float &x, float &y, float &z) const
{
	x = up[0];
	y = up[1];
	z = up[2];
}

void Camera::HandleKey(unsigned char key, int state, int x, int y)
{
	switch (key)
	{
		case 'A':
		case 'a':
			aKey = state;
            // printf("%f, %f, %f\n", eyePosition[0], eyePosition[1], eyePosition[2]);
			break;
		case 'D':
		case 'd':
			dKey = state;
			break;
		case 'W':
		case 'w':
			wKey = state;
			break;
		case 'S':
		case 's':
			sKey = state;
			break;
		case ' ':
			Reset();
		default:
			break;
        case 'N':
        case 'n':
            printf("Hello\n");
            break;
            
        // TODO: other keys
	}
}

void Camera::HandleMouse(int button, int state, int x, int y)
{
	currentButton = button;
	mouseX = x;
	mouseY = y;
}

void Camera::HandleMouseDrag(int x, int y)
{
	float rx, ry;
	float sensitivity = 0.01f; // speed of the camera moving

	// work out the difference between where the mouse was last used (mouseX, mouseY) to
	// position the view direction and the current position (x, y) the mouse is in
	rx = static_cast<float>(x - mouseX);
	ry = static_cast<float>(y - mouseY);

	// switch on which button was pressed and only do the update if the left button was pressed
	switch (currentButton)
	{
		case GLUT_LEFT_BUTTON:

			// add on the amount of change in to the left and right view direction of the camera
			if (rx > 0)
				add(vd, right, rx*sensitivity);
			else
				sub(vd, right, rx*-sensitivity);
			// add on the amount of change in to the up and down view direction of the camera
			if (ry > 0)
				sub(vd, up, ry*sensitivity);
			else
				add(vd, up, ry*-sensitivity);

			// normalise the view direction so it is length 1
			norm(vd);

			// use the view direction crossed with the up vector to obtain the corrected right vector
			cross(vd, up, right);

			// normalise the right vector
			norm(right);

			/* As we want out camera to stay on the same plane at the same height (i.e. not move up and down the y axis) update a forward direction vector which can be used to move the camera. This forward vector moves the camera in the same direction as the view direction except it will not contain any y component so it cannot move off of its original height. This was we are free to look up and down however moving forward and back will not move us off of the camera plane. */

			forward[0] = vd[0];
			forward[2] = vd[2];
			norm(forward);
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
	}

	mouseX = x;
	mouseY = y;
}
