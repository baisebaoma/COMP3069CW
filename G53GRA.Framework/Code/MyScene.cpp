#include "MyScene.h"

#include "Tree.h"
#include "Ground.hpp"
#include "Grass.hpp"
#include "Cloud.hpp"
// #include "Sky.hpp"
// #include "Rain.hpp"
#include "Sun.hpp"

#include <stdio.h>
#include <stdlib.h>


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	
}

void MyScene::Initialise()
{
    
    // good is to change the sky light. Change good in "MyScene.h", range from 0 to 1.
    GLfloat global_ambient[] = {good, good, good, 0.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
	glClearColor(good*128.f/255, good*178.f/255, good*228.f/255, 1.0f);  // the colour of sky
    glEnable(GL_TEXTURE_2D);  // enable texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // glEnable(GL_DEPTH_TEST);  // disable GL_DEPTH_TEST to make the trees' visualisation better
    
    // sun
    Sun *sun = new Sun();  // [IMPORTANT] use absolute path here
    AddObjectToScene(sun);
    
    /* original ones
    // cloud
    // You may try different textures such as "/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/cloud6.bmp", to see what's going on
    Cloud *cloud = new Cloud("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/cloud201.bmp");  // [IMPORTANT] use absolute path here
    AddObjectToScene(cloud);
    
    // ground
    Ground *g = new Ground("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/ground31.bmp");  // [IMPORTANT] use absolute path here
    AddObjectToScene(g);
    
    // tree
    // You may try different textures such as "/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/3.bmp", to see what's going on
    Tree *t = new Tree("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/101.bmp");   // [IMPORTANT] use absolute path here
	AddObjectToScene(t);
    
    // grass
    // here we add some random numbers to the grasses' position, to make it not so tidy
    float random_position[50][2];
    for(int i=0;i<50;i++){
        random_position[i][0] = float(rand()%10)/10;
        random_position[i][1] = float(rand()%10)/10;
        printf("%f, %f\n", random_position[i][0], random_position[i][1]);
    }
    // You may try different textures such as "/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/grass2.bmp", to see what's going on
    Grass *grass = new Grass("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/grass3.bmp", random_position);  // [IMPORTANT] use absolute path here
    AddObjectToScene(grass);
    
    // Rain *rain = new Rain("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/rain4.bmp");  // [IMPORTANT] use absolute path here
    // AddObjectToScene(rain);
     */
    
    // cloud
    // You may try different textures such as "cloud6.bmp", to see what's going on
    Cloud *cloud = new Cloud("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/cloud201.bmp");  // [IMPORTANT] use absolute path here
    AddObjectToScene(cloud);
    
    // ground
    Ground *g = new Ground("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/ground31.bmp");  // [IMPORTANT] use absolute path here
    AddObjectToScene(g);
    
    // tree
    // You may try different textures such as "3.bmp", to see what's going on
    Tree *t = new Tree("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/101.bmp");   // [IMPORTANT] use absolute path here
    AddObjectToScene(t);
    
    // grass
    // here we add some random numbers to the grasses' position, to make it not so tidy
    float random_position[50][2];
    for(int i=0;i<50;i++){
        random_position[i][0] = float(rand()%10)/10;
        random_position[i][1] = float(rand()%10)/10;
        printf("%f, %f\n", random_position[i][0], random_position[i][1]);
    }
    // You may try different textures such as "grass2.bmp", to see what's going on
    Grass *grass = new Grass("/Users/yiming/Library/Mobile Documents/com~apple~CloudDocs/Y4/ CGCW素材/grass3.bmp", random_position);  // [IMPORTANT] use absolute path here
    AddObjectToScene(grass);
    
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}
