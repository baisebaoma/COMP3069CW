#pragma once
/**
* Class for giving an coursework object input handling. Any class you want to have input handling
* should subclass the {@code public Input}. e.g. {@code MyObject : public DisplayableObject, public Input}
* <p>
* Methods will be called from a {@link Scene} renderer to give input from keyboard and mouse
* @see Camera
* @author wil
*/
class Input
{
public:
	Input(void){}
	virtual ~Input(void){}
	/**
	* Called when keyboard input is received from ASCII characters.
	* <p>
	* This includes keys ENTER (&#92;n), RETURN (&#92;cr), TAB (&#92;t), BACKSPACE (&#92;b), ESC (27), DELETE (127)
	* <p>
	* Note: check for RETURN and ENTER for cross-platform operability.
	* <p>
	* Example implementation:
	* {@code
	* 	void MyObject:HandleKey(unsigned char key, int state, int mX, int mY){
	* 	    if (state == 1){ // if key pressed down
	*	        switch(key){ // ASCII char
	*	            case 'A':
	* 	            case 'a':
	* 	                glTranslatef(-1.f,0.f,0.f); // go left
	*	                break;
	*	            case 'D':
	* 	            case 'd':
	* 	                glTranslate(1.f,0.f,0.f); // go right
	*	                break;
	* 	            case '\n':  // Windows and Linux
	* 	            case '\cr': // Mac OS X
	* 	                // operation for using enter/return key
	*	                break;
	*	        }
	*	    }
	*	}
	* }
	* @see #HandleSpecialKey(int key, int state, int x, int y)
	* @param key	ASCII character from keyboard input
	* @param state 1 if key down, 0 if key up
	* @param x    X coordinate of mouse in rendering window
	* @param y    Y coordinate of mouse in rendering window
	*/
	virtual void HandleKey(unsigned char key, int state, int x, int y) {};

	/**
	* Called when keyboard input is received from special (non-ASCII) characters.
	* <p>
	* key constants are named GLUT_KEY_* where * is the key. For example:
	* <p> (arrow keys) GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT,
	* <p> GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
	* <p> GLUT_KEY_F1, GLUT_KEY_F2, etc.
	* <p>
	* Example implementation:
	* {@code
	* 	void MyObject::HandleKey(unsigned int key, int state, int x, int y){
	* 	    if (state == 1){ // if key pressed down
	*	        switch(key){ // special key
	*	            case GLUT_KEY_LEFT:
	* 	                glTranslate(-1.f,0.f,0.f); // go left
	*	                break;
	*	            case GLUT_KEY_RIGHT:
	* 	                glTranslate(1.f,0.f,0.f); // go right
	*	                break;
	*	        }
	*	    }
	*	}
	* }
	* @see #HandleKey(char key, int state, int x, int y)
	* @param key coded keyboard input
	* @param state 1 if key down, 0 if key up
	* @param x	X coordinate of mouse in rendering window
	* @param y	Y coordinate of mouse in rendering window
	*/
	virtual void HandleSpecialKey(int key, int state, int x, int y) {};

	/**
	* Called when mouse is clicked up / down in the rendering window
	* <p>
	* button constants: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON and GLUT_MIDDLE_BUTTON
	* @see #HandleMouseDrag(int x, int y)
	* @see #HandleMouseMove(int x, int y)
	* @param button mouse button (GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON or GLUT_MIDDLE_BUTTON)
	* @param state 1 if mouse down, 0 if mouse up
	* @param x X coordinate of mouse in rendering window
	* @param y Y coordinate of mouse in rendering window
	*/
	virtual void HandleMouse(int button, int state, int x, int y)      {};

	/**
	* Called when mouse is moved in rendering window while mouse button is held down
	* @see #HandleMouse(int button, int state, int x, int y)
	* @see #HandleMouseMove(int x, int y)
	* @param x	X coordinate of mouse in rendering window
	* @param y	Y coordinate of mouse in rendering window
	*/
	virtual void HandleMouseDrag(int x, int y)						   {};

	/**
	* Called when mouse is moved in rendering window when no mouse button is pressed
	* @see #HandleMouse(int button, int state, int x, int y)
	* @see #HandleMouseDrag(int x, int y)
	* @param x	X coordinate of mouse in rendering window
	* @param y	Y coordinate of mouse in rendering window
	*/
	virtual void HandleMouseMove(int x, int y)						   {};

/*
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y);
*/
};