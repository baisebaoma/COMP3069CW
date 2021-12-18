#pragma once

#ifdef _WIN32
#include <GL/glut.h>
#include <Windows.h>
#else
#include <GLUT/glut.h>
#endif
/**
  * Base Engine for the framework. Handles windowing and freeglut/OpenGL contexts.
  * Engine is static.
  */
class Engine
{
public:
	/**
	* Constructor takes in command line arguments, a title and initial window dimensions.
	*/
	Engine(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	virtual ~Engine(){};
	/**
	 * Initial startup method. Sets up GL context and windowing functions to handle drawing, timing and input.
	 */
	virtual void Run();
	/**
	 * Returns self.
	 */
	static Engine* GetCurrentInstance();
	/** Returns window title */
	static const char* GetWindowTitle();
	/** Returns window id */
	static int GetWindowID();
	/** Returns window width */
	static int GetWindowWidth();
	/** Returns window height */
	static int GetWindowHeight();

protected:
	/** pointer to current window context */
	static Engine *current;

	static const char* windowTitle;
	static int windowID;
	static int windowWidth;
	static int windowHeight;
	static int time;

	/** Sets up default initial functionality for window */
	static void InitFunc();
	/** Calls {@link Draw} and handles double buffering */
	static void DrawFunc();
	/** Checks runtime between successive calls and runs {@link Update} before pushing redisplay */
	static void IdleFunc();
	/** Handles window resize */
	static void ResizeFunc(int _width, int _height);
	/** Handles key press */
	static void KeyDownFunc(unsigned char key, int x, int y);
	/** Handles key release */
	static void KeyUpFunc(unsigned char key, int x, int y);
	/** Handles special key press */
	static void SpecialKeyDownFunc(int key, int x, int y);
	/** Handles special key release */
	static void SpecialKeyUpFunc(int key, int x, int y);
	/** Handles mouse button click */
	static void MouseFunc(int button, int state, int x, int y);
	/** Handles mouse click and drag (active motion) */
	static void MouseMotionFunc(int x, int y);
	/** Handles mouse movement (passive motion) */
	static void PassiveMouseMotionFunc(int x, int y);

	// Pure virtual functions handled overloaded by Scene
	virtual void Initialise() = 0;
	virtual void Draw() = 0;
	virtual void Reshape(int w, int h) = 0;
	virtual void Update(const double&) = 0;
	virtual void HandleKey(unsigned char key, int state, int x, int y) = 0;
	virtual void HandleSpecialKey(int key, int state, int x, int y) = 0;
	virtual void HandleMouse(int button, int state, int x, int y) = 0;
	virtual void HandleMouseDrag(int x, int y) = 0;
	virtual void HandleMouseMove(int x, int y) = 0;

	/**
	 * Iterates through OpenGL error list and dumps error information to console.
	 * <p>
	 * Call this method in a draw loop.
	 */
	static int CheckGLError();
};

