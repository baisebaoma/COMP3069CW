#pragma once
/**
 * Default setup for G53GRA Coursework. You should subclass {@code Scene} and add your functionality.
 * Override {@link #Initialise()} to add {@link DisplayableObject}s to your {@code Scene}. Running your
 * subclass will setup and draw objects based on your {@link #Initialise()} function.
 * <p>
 * <b>Functions that can be overloaded: </b>
 * <br>{@link #Initialise()}<br>{@link #Projection()}<br>{@link #Reshape()}
 * <br>{@link #Update()} <b>(advanced)</b>
 * @author wil
 */
#include "Engine.h"		//! Superclass for accessing OpenGL/Context windowing
#include "../Utility/Texture.h"	//! Handles Texture loading for bitmap images
#include "../Utility/Camera.h"  //! Camera class
#include <vector>		//! Utility for maintaining DispalyableObjects in system

class DisplayableObject; // Anonymous

class Scene : public Engine
{
public:
	/**
	 * Constructor, overrides Engine() and takes in command line arguments, a title and initial window dimensions.
	 */
	Scene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	virtual ~Scene();

	/** Return window width */
	static int GetWindowWidth();
	/** Return window height */
	static int GetWindowHeight();
	/**
	 * Input a .bmp bitmap image to bind to internal texture buffer
	 * @returns textureID
	 * @params fileName the name of the texture file you want to input
	 */
	static int GetTexture(std::string fileName);
	/** Returns a pointer to the Camera */
	static Camera* GetCamera() {
		return &camera;
	}

protected:
	/**
	* This must be overloaded this to add {@link DisplayableObject}s to your
	* scene.
	* @see #Projection()
	*/
	virtual void Initialise() = 0;
	/**
	 * This function will loop continuously until the program is exited. It will iterate through the objects and render in your Scene
	 * <p>
	 * The frequency at which {@code Draw()} is called per second is dependent on your hardware and scene,
	 * so for animation, you MUST use the {@link #Update} method with {@code deltaTime}
	 * <p>
	 * It is strongly recommended you do NOT attempt to override this method.
	 * <p>
	 * {@code Draw()} should NEVER be called explicitly.
	 * @see #Reshape()
	 */
	void Draw();
	/**
	* Called when the window is resized, and handles resizing events.
	* <p>
	* You should this function to handle the window being resized. The default property is to update the
	* projection parameters. You can access the window size parameters by the {@code w} and {@code h} variables.
	* For example, you could overload this function to adjust the size of all objects in your {@code Scene}.
	* @see #Draw()
	* @see #Projection()
	* @see #Initialise()
	*/
	void Reshape(int w, int h);
	/**
	 * Sets the projection properties of the scene. Override to change projection properties.
	 * <p>
	 * Default: Orthographic mode
	 */
	virtual void Projection();

	/**
	* The update function for {@link Camera} and {@link Animation}. Calculates the time-delay since
	* the last update and passes as a parameter to the respective class's {@code Update()} functions.
	* <p>
	* You should only override this class if you want to change how the animation update function works.
	* This is not advised.
	* @see Camera
	* @see Animation
	* @see #Draw()
	*/
	void Update(const double& deltaTime);

	// Input handling methods
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y);

	/**
	* Adds a {@link DisplayableObject} (includes {@link Animation}s) to the {@link Scene}.
	* <p>
	* It is strongly recommended you do NOT attempt to override this method.
	* @see #addObjectToScene(DisplayableObject, String)
	* @see #getObject(String)
	* @param obj DisplayableObject to be added to the scene.
	*/
	void AddObjectToScene(DisplayableObject *obj);

private:
	/**
	* Scene camera. Contains viewing properties. Defaults to framework {@link Camera} class.
	* Overload {@link #Initialise()} to set a different {@link Camera}.
	*/
	static Camera camera;
	/**
	 * Texture manager for binding bitmap images as GL_TEXTURE2D IDs
	 */
	static Texture texture;
	/**
	* Vector containing all {@link DisplayableObject}s in the scene.
	* @see DisplayableObject
	* @see #AddObjectToScene(DisplayableObject)
	*/
	std::vector<DisplayableObject*> objects;
};
