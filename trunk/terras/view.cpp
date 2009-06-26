
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "controller.h"
#include "view.h"


// Process pending events



TerraView::TerraView(){

	info = SDL_GetVideoInfo();	
	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
	if (info->hw_available) {vidFlags |= SDL_HWSURFACE;}
	else {vidFlags |= SDL_SWSURFACE;}
	bpp = info->vfmt->BitsPerPixel;
	SDL_SetVideoMode(window_width, window_height, bpp, vidFlags);
	/* Setup SDL */
	glViewport( 0, 0, window_width, window_height );
	glMatrixMode( GL_PROJECTION );
	glEnable( GL_DEPTH_TEST );
	gluPerspective( 45, (float)window_width/window_height, 0.1, 100 );
	glMatrixMode( GL_MODELVIEW );

	return;
}

void TerraView::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(0,0,-10);

	glRotatef(yangle, 1, 0, 0);
	glRotatef(xangle, 0, 1, 0);

	glBegin(GL_QUADS);
	glColor3ub(000, 000, 000); 
	glVertex3f(-1,-1,-1);
	glColor3ub(000, 000, 255);
	glVertex3f(-1,-1, 1);
	glColor3ub(000, 255, 255);
	glVertex3f(-1, 1, 1);
	glColor3ub(000, 255, 000);
	glVertex3f(-1, 1,-1);

	glColor3ub(000,000,000);
	glVertex3f(-1,-1,-1);
	glColor3ub(000,255,000);
	glVertex3f(-1, 1,-1);
	glColor3ub(255,255,000);
	glVertex3f( 1, 1,-1);
	glColor3ub(255,000,000);
	glVertex3f( 1,-1,-1);

	glColor3ub(000,000,000);
	glVertex3f(-1,-1,-1);
	glColor3ub(255,000,000);
	glVertex3f( 1,-1,-1);
	glColor3ub(255,000,255);
	glVertex3f( 1,-1, 1);
	glColor3ub(000,000,255);
	glVertex3f(-1,-1, 1);

	glColor3ub(255, 255, 255); 
	glVertex3f( 1, 1, 1);
	glColor3ub(255, 255, 000);
	glVertex3f( 1, 1,-1);
	glColor3ub(255, 000, 000);
	glVertex3f( 1,-1,-1);
	glColor3ub(255, 000, 255);
	glVertex3f( 1,-1, 1);

	glColor3ub(255, 255, 255); 
	glVertex3f( 1, 1, 1);
	glColor3ub(255, 255, 000);
	glVertex3f( 1, 1,-1);
	glColor3ub(255, 000, 000);
	glVertex3f( 1,-1,-1);
	glColor3ub(255, 000, 255);
	glVertex3f( 1,-1, 1);

	glColor3ub(255, 255, 255); 
	glVertex3f( 1, 1, 1);
	glColor3ub(255, 000, 255);
	glVertex3f( 1,-1, 1);
	glColor3ub(000, 000, 255);
	glVertex3f(-1,-1, 1);
	glColor3ub(000, 255, 255);
	glVertex3f(-1, 1, 1);

	glColor3ub(255, 255, 255); 
	glVertex3f( 1, 1, 1);
	glColor3ub(255, 255, 000);
	glVertex3f( 1, 1,-1);
	glColor3ub(000, 255, 000);
	glVertex3f(-1, 1,-1);
	glColor3ub(000, 255, 255);
	glVertex3f(-1, 1, 1);

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