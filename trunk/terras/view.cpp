#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <yaml.h>

#include "types.h"
#include "controller.h"
#include "node.h"
#include "view.h"
#include "cursor.h"
#include "sdltextures.h"

/** Set default values for configuration options and initialize the appropriate
 * SDL systems. */
View::View(Controller *newController, Model *newModel){
	controller = newController;
	model = newModel;
	xangle = 0; yangle = 0;
	cursor = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf( stderr, "SDL Video initialization failed: %s\n",
			SDL_GetError() );
		exit(1);
	}

	init();
	initGL();
	cursor = new Cursor(this);
}

View::~View(){
	if(cursor != NULL)
		delete cursor;
}


/** Initialize SDL */
void View::init(){
	info = SDL_GetVideoInfo();	
	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
	if (info->hw_available) {vidFlags |= SDL_HWSURFACE;}
	else {vidFlags |= SDL_SWSURFACE;}
	bpp = info->vfmt->BitsPerPixel;

	printf("Initializing SDL to %dx%dx%d\n", controller->config.width, 
		controller->config.height, bpp);
	window = SDL_SetVideoMode(controller->config.width, 
		controller->config.height, bpp, vidFlags);

	if(!window){
		SDL_Quit();
		exit(1);
	}
	
	SDL_WM_SetCaption(controller->config.title.c_str(), NULL);
	if(controller->config.fullscreen){
		//printf("Would switch to fullscreen\n");
		SDL_WM_ToggleFullScreen(window);

		SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_ShowCursor(SDL_DISABLE);
	}
}

/** Initialize OpenGL */
void View::initGL(){

	glEnable(GL_TEXTURE_2D);
	glViewport( 0, 0, controller->config.width, controller->config.height );

	glMatrixMode( GL_PROJECTION );
	gluPerspective( controller->config.fov,
		(float)controller->config.width/controller->config.height, 0.1, 100 );
	glMatrixMode( GL_MODELVIEW );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	/* We don't need depth testing or lighting, so it's not enabled */
	//glEnable( GL_DEPTH_TEST );
	//glDisable (GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	return;
}

/** Set the controller referenced from this view. */
void View::setController(Controller *c){
	controller = c;
}

/** Set current node. */
void View::setCurrentNode(Node *newNode){
	currNode = newNode;
}

/** Renders the view through OpenGL. */
void View::draw(){
	draw3D();
	draw2D();

	SDL_GL_SwapBuffers();
}

/** Renders 2D things in the event loop.  These are drawn over the 3D images
 * because of the order in which these are called.
 */
void View::draw2D(){
	/* Set 2D rendering mode */
	int vPort[4], x, y;

	glGetIntegerv(GL_VIEWPORT, vPort);
	//printf("vPort: %d,%d\n",vPort[2],vPort[3]);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	/* Create a unit-axis Orthogonal view */
	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//glColor3f(0,0,0);

	SDL_GetMouseState(&x,&y);
	y = window->h - y;

	cursor->setCoords(x,y);
	cursor->draw();

	/* Reset rendering mode */
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

/** Renders the cube in the main event loop.
 * A word on notation: we take North as -z, the original camera position, and
 * define everything else in terms of this. Thus, 
 * - North is -z
 * - East is +x
 * - South is +z
 * - West is -x
 * - Up is +y
 * - Down is -y
 */
void View::draw3D(){
	/* Shortcut */
	cubemap_t *im = currNode->getImagemap();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1,1,1);
	//glTranslatef(0,0,-10);

	glRotatef(yangle, 1, 0, 0);
	glRotatef(xangle, 0, 1, 0);

	
	/* NORTH FACE */
	glBindTexture(GL_TEXTURE_2D, im->glNames[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(im->coords[0][0],im->coords[0][3]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(im->coords[0][2],im->coords[0][3]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(im->coords[0][2],im->coords[0][1]);
	glVertex3f( 1, 1,-1);
	glTexCoord2f(im->coords[0][0],im->coords[0][1]);
	glVertex3f(-1, 1,-1);
	glEnd();

	/* EAST FACE */
	glBindTexture(GL_TEXTURE_2D, im->glNames[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(im->coords[1][0],im->coords[1][3]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(im->coords[1][2],im->coords[1][3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(im->coords[1][2],im->coords[1][1]);
	glVertex3f( 1, 1, 1);
	glTexCoord2f(im->coords[1][0],im->coords[1][1]);
	glVertex3f( 1, 1,-1);
	glEnd();

	/* SOUTH FACE */
	glBindTexture(GL_TEXTURE_2D, im->glNames[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(im->coords[2][0],im->coords[2][3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(im->coords[2][2],im->coords[2][3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(im->coords[2][2],im->coords[2][1]);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(im->coords[2][0],im->coords[2][1]);
	glVertex3f( 1, 1, 1);
	glEnd();

	/* WEST FACE */
	glBindTexture(GL_TEXTURE_2D, im->glNames[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(im->coords[3][0],im->coords[3][3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(im->coords[3][2],im->coords[3][3]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(im->coords[3][2],im->coords[3][1]);
	glVertex3f(-1, 1,-1);
	glTexCoord2f(im->coords[3][0],im->coords[3][1]);
	glVertex3f(-1, 1, 1);
	glEnd();

	/* UP FACE */
	glBindTexture(GL_TEXTURE_2D, im->glNames[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(im->coords[4][0],im->coords[4][3]);
	glVertex3f(-1, 1,-1);
	glTexCoord2f(im->coords[4][2],im->coords[4][3]);
	glVertex3f( 1, 1,-1);
	glTexCoord2f(im->coords[4][2],im->coords[4][1]);
	glVertex3f( 1, 1, 1);
	glTexCoord2f(im->coords[4][0],im->coords[4][1]);
	glVertex3f(-1, 1, 1);
	glEnd();

	/* DOWN FACE */
	glBindTexture(GL_TEXTURE_2D, im->glNames[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(im->coords[5][0],im->coords[5][3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(im->coords[5][2],im->coords[5][3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(im->coords[5][2],im->coords[5][1]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(im->coords[5][0],im->coords[5][1]);
	glVertex3f(-1,-1,-1);
	glEnd();
}

void View::moveCursor(double x, double y){
// 	printf("Adjusting angle: %+1.1f, %+1.1f\n",x,y);
	if(cursor->isLocked()){
		xangle += x * controller->config.sensitivity;
		yangle += y * controller->config.sensitivity;
		// Limits on vertical movement
		if(yangle >  90) yangle =  90;
		if(yangle < -90) yangle = -90;
		// Limit on horizontal moment, so that it's continuous.
		if(fabs(xangle) > 180.0) xangle = fmod(xangle,360.0);
		return;
	} else return;
}

Cursor *View::getCursor(){
	return cursor;
}
