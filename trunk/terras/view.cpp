#include <fstream>
#include <iostream>
#include <vector>

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
#include "sdltextures.h"

/** Set default values for configuration options. */
TerraView::TerraView(){
	xangle = 0; yangle = 0;
}

/** Initialize SDL */
void TerraView::init(){
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
	if(controller->config.fullscreen)
		//printf("Would switch to fullscreen\n");
		SDL_WM_ToggleFullScreen(window);
}

/** Initialize OpenGL */
void TerraView::initGL(){
// 	SDL_Surface *cursorSurf;
// 	cursorSurf = IMG_Load("data/cursors/fwd.png");
// 	cursor = SDL_GL_LoadTexture(cursorSurf, cursor_coords);
// 	SDL_FreeSurface(cursorSurf);
// 	printf("cursor: %d\n",cursor);

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


	return;
}

void TerraView::setController(TerraController *c){
	controller = c;
}

/** Set current node. */
void TerraView::setCurrentNode(TerraNode *newNode){
	currNode = newNode;
}

/** Renders the view through OpenGL.
 */
void TerraView::draw(){
	draw3D();
	draw2D();

	SDL_GL_SwapBuffers();
}

/** Draw the cursor on the screen.  This is done in 2D mode.
 * The cursor should get several different modes, so this will obviously 
 * have to expand.
 *
 * This should always be the last 2D drawing function called, so that the
 * cursor is on top.
 */
void TerraView::drawCursor(){
	int x,y;
	SDL_GetMouseState(&x,&y);
	y = window->h - y;
	
// 	glBindTexture(GL_TEXTURE_2D,cursor);
	glBegin(GL_QUADS);
// 	glTexCoord2f(cursor_coords[0],cursor_coords[3]);
	glVertex2i(x,y);
// 	glTexCoord2f(cursor_coords[1],cursor_coords[3]);
	glVertex2i(x+CURSOR_SIZE,y);
// 	glTexCoord2f(cursor_coords[1],cursor_coords[2]);
	glVertex2i(x+CURSOR_SIZE,y-CURSOR_SIZE);
// 	glTexCoord2f(cursor_coords[0],cursor_coords[2]);
	glVertex2i(x, y-CURSOR_SIZE);
	glEnd();
}

/** Renders 2D things in the event loop.  These are drawn over the 3D images
 * because of the order in which these are called.
 */
void TerraView::draw2D(){
	/* Set 2D rendering mode */
	int vPort[4];
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
	glColor3f(0,0,0);

	drawCursor();

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
void TerraView::draw3D(){
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

void TerraView::adjustAngle(double x, double y){
// 	printf("Adjusting angle: %+1.1f, %+1.1f\n",x,y);
	xangle += x * controller->config.sensitivity;
	yangle += y * controller->config.sensitivity;
	// Limits on vertical movement
	if(yangle >  90) yangle =  90;
	if(yangle < -90) yangle = -90;
	return;
}