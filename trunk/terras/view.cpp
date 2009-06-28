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


TerraView::TerraView(){
	xangle = 0; yangle = 0;
}

void TerraView::init(){
	info = SDL_GetVideoInfo();	
	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
	if (info->hw_available) {vidFlags |= SDL_HWSURFACE;}
	else {vidFlags |= SDL_SWSURFACE;}
	bpp = info->vfmt->BitsPerPixel;

	printf("Initializing SDL to %dx%d\n", controller->config.width, 
		controller->config.height);
	window = SDL_SetVideoMode(controller->config.width, 
		controller->config.height, bpp, vidFlags);

	if(!window){
		SDL_Quit();
		exit(1);
	}
	
	SDL_WM_SetCaption(controller->config.title.c_str(), NULL);
	if(controller->config.fullscreen)
		printf("Would switch to fullscreen\n");
		//SDL_WM_ToggleFullScreen(window);
}

void TerraView::initGL(){
	/* Setup SDL */
	loadTextures();

	glEnable(GL_TEXTURE_2D);
	glViewport( 0, 0, controller->config.width, controller->config.height );
	glMatrixMode( GL_PROJECTION );
	glEnable( GL_DEPTH_TEST );
	gluPerspective( controller->config.fov,
		(float)controller->config.width/controller->config.height, 
		0.1, 100 );
	glMatrixMode( GL_MODELVIEW );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable (GL_LIGHTING);

	
	return;
}


void TerraView::loadTextures(){
	SDL_Surface *image;
	//glGenTextures(6,texture);

	image=IMG_Load("test/stormy0.jpg");
	if(!image) printf("IMG_Load: %s\n", IMG_GetError());
	texture[0] = SDL_GL_LoadTexture(image, texcoords[0]);
	SDL_FreeSurface(image);

	image=IMG_Load("test/stormy1.jpg");
	if(!image) printf("IMG_Load: %s\n", IMG_GetError());
	texture[1] = SDL_GL_LoadTexture(image, texcoords[1]);
	SDL_FreeSurface(image);

	image=IMG_Load("test/stormy2.jpg");
	if(!image) printf("IMG_Load: %s\n", IMG_GetError());
	texture[2] = SDL_GL_LoadTexture(image, texcoords[2]);
	SDL_FreeSurface(image);

	image=IMG_Load("test/stormy3.jpg");
	if(!image) printf("IMG_Load: %s\n", IMG_GetError());
	texture[3] = SDL_GL_LoadTexture(image, texcoords[3]);
	SDL_FreeSurface(image);

	image=IMG_Load("test/stormy4.jpg");
	if(!image) printf("IMG_Load: %s\n", IMG_GetError());
	texture[4] = SDL_GL_LoadTexture(image, texcoords[4]);
	SDL_FreeSurface(image);

	image=IMG_Load("test/stormy5.jpg");
	if(!image) printf("IMG_Load: %s\n", IMG_GetError());
	texture[5] = SDL_GL_LoadTexture(image, texcoords[5]);
	SDL_FreeSurface(image);

// 	printf("OpenGL texture names: %d, %d, %d, %d, %d, %d\n",
// 		texture[0],texture[1],texture[2],texture[3],texture[4],texture[5]);
}

void TerraView::setController(TerraController *c){
	controller = c;
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
void TerraView::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(0,0,-10);

	glRotatef(yangle, 1, 0, 0);
	glRotatef(xangle, 0, 1, 0);

	
	/* NORTH FACE */
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(texcoords[0][0],texcoords[0][3]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(texcoords[0][2],texcoords[0][3]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(texcoords[0][2],texcoords[0][1]);
	glVertex3f( 1, 1,-1);
	glTexCoord2f(texcoords[0][0],texcoords[0][1]);
	glVertex3f(-1, 1,-1);
	glEnd();

	/* EAST FACE */
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(texcoords[1][0],texcoords[1][3]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(texcoords[1][2],texcoords[1][3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(texcoords[1][2],texcoords[1][1]);
	glVertex3f( 1, 1, 1);
	glTexCoord2f(texcoords[1][0],texcoords[1][1]);
	glVertex3f( 1, 1,-1);
	glEnd();

	/* SOUTH FACE */
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(texcoords[2][0],texcoords[2][3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(texcoords[2][2],texcoords[2][3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(texcoords[2][2],texcoords[2][1]);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(texcoords[2][0],texcoords[2][1]);
	glVertex3f( 1, 1, 1);
	glEnd();

	/* WEST FACE */
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(texcoords[3][0],texcoords[3][3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(texcoords[3][2],texcoords[3][3]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(texcoords[3][2],texcoords[3][1]);
	glVertex3f(-1, 1,-1);
	glTexCoord2f(texcoords[3][0],texcoords[3][1]);
	glVertex3f(-1, 1, 1);
	glEnd();

	/* UP FACE */
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(texcoords[4][0],texcoords[4][3]);
	glVertex3f(-1, 1,-1);
	glTexCoord2f(texcoords[4][2],texcoords[4][3]);
	glVertex3f( 1, 1,-1);
	glTexCoord2f(texcoords[4][2],texcoords[4][1]);
	glVertex3f( 1, 1, 1);
	glTexCoord2f(texcoords[4][0],texcoords[4][1]);
	glVertex3f(-1, 1, 1);
	glEnd();

	/* DOWN FACE */
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(texcoords[5][0],texcoords[5][3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(texcoords[5][2],texcoords[5][3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(texcoords[5][2],texcoords[5][1]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(texcoords[5][0],texcoords[5][1]);
	glVertex3f(-1,-1,-1);
	glEnd();

	SDL_GL_SwapBuffers();
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