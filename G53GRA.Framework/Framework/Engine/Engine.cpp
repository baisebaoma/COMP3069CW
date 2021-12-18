#include "Engine.h"
#include <string>

Engine *Engine::current = 0;
const char* Engine::windowTitle = "";
int Engine::windowID = 0;
int Engine::windowWidth = 0;
int Engine::windowHeight = 0;
int Engine::time = 0;

Engine::Engine(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
{
	Engine::windowWidth = windowWidth;
	Engine::windowHeight = windowHeight;
	Engine::windowTitle = title;

	glutInit(&argc, argv);
}

void Engine::Run()
{
	// Initialise OpenGL Context
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	windowID = glutCreateWindow(windowTitle);
	current = this;

	// Rendering Functions
	glutDisplayFunc(DrawFunc);
	glutReshapeFunc(ResizeFunc);
	glutIdleFunc(IdleFunc);

	// Peripheral Input Handling
	glutKeyboardFunc(KeyDownFunc);
	glutKeyboardUpFunc(KeyUpFunc);
	glutSpecialFunc(SpecialKeyDownFunc);
	glutSpecialUpFunc(SpecialKeyUpFunc);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotionFunc);
	glutPassiveMotionFunc(PassiveMouseMotionFunc);

	InitFunc();

	printf("Setup complete. Window created [%dx%d]\n", windowWidth, windowHeight);
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	glutMainLoop();
}

void Engine::InitFunc()
{
	// Default background colour
	glClearColor(static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(1.0f));

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable backface culling
	glEnable(GL_CULL_FACE);

	// Enable transparency blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable 2-D texturing
	glEnable(GL_TEXTURE_2D);

	// Enable blending colour information with texture information
	glEnable(GL_COLOR_MATERIAL);

	// Turn off 2 sided lighting
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    /*
	// set the ambient light model
	GLfloat global_ambient[] = {1.f, 1.f, 1.f, 0.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
     */

	// enable directional light lighting
	// (x, y, z, 0.0) -> directional lighting
	// (x, y, z, 1.0) -> positional lighting
    
	glEnable(GL_LIGHTING);
	GLfloat ambience[] = {0.0f, 0.0f, 0.0f, 1.0f}; // 不能开
	GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat specular[] = {0.0f, 0.0f, 0.0f, 0.0f}; // 没用
	GLfloat position[] = {1.0f, 1.0f, 1.0f, 0.0f}; // 不用改
    
    /*
    // original below
    GLfloat ambience[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[] = {1.0f, 1.0f, 1.0f, 0.0f};
     */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	// Enable smooth shading from lighting
	glShadeModel(GL_SMOOTH);

	// Enable automatic normalisation of normal vectors
	glEnable(GL_NORMALIZE);

	current->Initialise();
	time = 0;

}


void Engine::DrawFunc()
{
	current->Draw();
	glutSwapBuffers();
}

void Engine::ResizeFunc(int w, int h)
{
	Engine::windowWidth = w;
	Engine::windowHeight = h;
	current->Reshape(w, h);
}

void Engine::KeyDownFunc(unsigned char key, int x, int y)
{
	current->HandleKey(key, 1, x, y);
}

void Engine::KeyUpFunc(unsigned char key, int x, int y)
{
	current->HandleKey(key, 0, x, y);
}

void Engine::SpecialKeyDownFunc(int key, int x, int y)
{
	current->HandleSpecialKey(key, 1, x, y);
}

void Engine::SpecialKeyUpFunc(int key, int x, int y)
{
	current->HandleSpecialKey(key, 0, x, y);

}

void Engine::MouseFunc(int button, int state, int x, int y)
{
	current->HandleMouse(button, state, x, y);
}

void Engine::MouseMotionFunc(int x, int y)
{
	current->HandleMouseDrag(x, y);
}

void Engine::PassiveMouseMotionFunc(int x, int y)
{
	current->HandleMouseMove(x, y);
}

void Engine::IdleFunc()
{
	// Get elapsed time (milliseconds)
	int t = glutGet(GLUT_ELAPSED_TIME);
	// Calculate difference in seconds between previous and current call 
	double diff = static_cast<double>(t - time) / 1000.0;
	time = t;
	// Call Update methods
	current->Update(diff);
	// Signify flag for display/bufferswap
	glutPostRedisplay();
}

int Engine::CheckGLError()
{
	int e = 0;
	GLenum error = glGetError();
	while (GL_NO_ERROR != error)
	{
		++e;
		printf("GL Error %i: %s\n", e, gluErrorString(error));
		error = glGetError();
	}

	return e;
}

Engine* Engine::GetCurrentInstance()
{
	return Engine::current;
}

const char* Engine::GetWindowTitle()
{
	return Engine::windowTitle;
}

int Engine::GetWindowID()
{
	return Engine::windowID;
}

int Engine::GetWindowWidth()
{
	return Engine::windowWidth;
}

int Engine::GetWindowHeight(){
	return Engine::windowHeight;
}
