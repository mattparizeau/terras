
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "controller.h"
#include "node.h"
#include "view.h"
#include "sdltextures.h"



// Process pending events



TerraView::TerraView(){
	info = SDL_GetVideoInfo();
	xangle = 0; yangle = 0;
}

void TerraView::init(){
	info = SDL_GetVideoInfo();	
	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
	if (info->hw_available) {vidFlags |= SDL_HWSURFACE;}
	else {vidFlags |= SDL_SWSURFACE;}
	bpp = info->vfmt->BitsPerPixel;
	
	window = SDL_SetVideoMode(window_width, window_height, bpp, vidFlags);
	if(!window){
		SDL_Quit();
		exit(1);
	}
}

void TerraView::initGL(){
	/* Setup SDL */
	glEnable(GL_TEXTURE_2D);
	glViewport( 0, 0, window_width, window_height );
	glMatrixMode( GL_PROJECTION );
	glEnable( GL_DEPTH_TEST );
	gluPerspective( FOV, (float)window_width/window_height, 0.1, 100 );
	glMatrixMode( GL_MODELVIEW );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable (GL_LIGHTING);

	loadTextures();
	return;
}

void TerraView::loadTextures(){
	SDL_Surface *image;
	image=IMG_Load("nehe.bmp");
	if(!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	//printf("Image loaded\n");
	texture = SDL_GL_LoadTexture(image, texcoords);
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

	glBegin(GL_QUADS);
	/* NORTH FACE */
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(texcoords[0],texcoords[3]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(texcoords[2],texcoords[3]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(texcoords[2],texcoords[1]);
	glVertex3f( 1, 1,-1);
	glTexCoord2f(texcoords[0],texcoords[1]);
	glVertex3f(-1, 1,-1);

	/* EAST FACE */
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(texcoords[0],texcoords[3]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(texcoords[2],texcoords[3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(texcoords[2],texcoords[1]);
	glVertex3f( 1, 1, 1);
	glTexCoord2f(texcoords[0],texcoords[1]);
	glVertex3f( 1, 1,-1);

	/* SOUTH FACE */
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(texcoords[0],texcoords[3]);
	glVertex3f( 1,-1, 1);
	glTexCoord2f(texcoords[2],texcoords[3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(texcoords[2],texcoords[1]);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(texcoords[0],texcoords[1]);
	glVertex3f( 1, 1, 1);

	/* WEST FACE */
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(texcoords[0],texcoords[3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(texcoords[2],texcoords[3]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(texcoords[2],texcoords[1]);
	glVertex3f(-1, 1,-1);
	glTexCoord2f(texcoords[0],texcoords[1]);
	glVertex3f(-1, 1, 1);

	/* UP FACE */
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(texcoords[2],texcoords[3]);
	glVertex3f( 1, 1,-1);
	glTexCoord2f(texcoords[0],texcoords[3]);
	glVertex3f(-1, 1,-1);
	glTexCoord2f(texcoords[0],texcoords[1]);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(texcoords[2],texcoords[1]);
	glVertex3f( 1, 1, 1);

	/* DOWN FACE */
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexCoord2f(texcoords[2],texcoords[1]);
	glVertex3f( 1,-1,-1);
	glTexCoord2f(texcoords[0],texcoords[1]);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(texcoords[0],texcoords[3]);
	glVertex3f(-1,-1, 1);
	glTexCoord2f(texcoords[2],texcoords[3]);
	glVertex3f( 1,-1, 1);
	
	glEnd();
	SDL_GL_SwapBuffers();
}

void TerraView::adjustAngle(double x, double y){
// 	printf("Adjusting angle: %+1.1f, %+1.1f\n",x,y);
	xangle += x;
	yangle += y;
	// Limits on vertical movement
	if(yangle >  90) yangle =  90;
	if(yangle < -90) yangle = -90;
	return;
}