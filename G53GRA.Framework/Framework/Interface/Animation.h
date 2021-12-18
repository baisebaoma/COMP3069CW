#pragma once
/**
* Class to be subclassed alongside DisplayableObject for all animated objects to be displayed in a Scene
* <p>
* Contains {@link #Update} method that must be overloaded. {@link #Update(float deltaTime)} is called from {@link Scene}.
*
* @author wil
*/
class Animation
{
public:
	Animation(void){}
	virtual ~Animation(void){}
	/**
	* Called each frame to update. Must be defined!
	* <p>
	* Use this to update animation sequence.
	* @param deltaTime change in time since previous call
	*/
	virtual void Update(const double& deltaTime) = 0;
};