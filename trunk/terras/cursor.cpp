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
#include "view.h"
#include "cursor.h"
#include "sdltextures.h"

/** Create the cursor object.  This loads appropriate cursor textures. */
Cursor::Cursor(View *newView){
	/* Initialization */
	mode = CURSOR_POINTER;
	view = newView;
	lock = false;

	/* Load textures */
// 	img = IMG_Load(FILE_CURSOR_POINTER);
// 	if(!img) {
// 		printf("CURSOR: Cannot load %s: %s\n",FILE_CURSOR_POINTER, IMG_GetError());
// 	}
	glNames[CURSOR_POINTER] = SDL_GL_LoadTextureFile(FILE_CURSOR_POINTER,
		cursor_coords[CURSOR_POINTER]);
// 	printf("Cursor is %d\n", glNames[CURSOR_POINTER]);
// 	SDL_FreeSurface(img);
}

/** Delete the cursor object, freeing the associated textures. */
Cursor::~Cursor(){
	glDeleteTextures(NUM_CURSORS, glNames);
}

/** Set the location of the cursor. */
void Cursor::setCoords(int x1,int y1){
	if(lock){
		x = view->window->w / 2;
		y = view->window->h / 2;
		//SDL_WarpMouse(x,y);
		return;
	}
	x = x1; y = y1;
}

/** Toggle current cursor lock status. */
bool Cursor::toggleLock(){
	//printf("Toggling cursor lock...\n");

	x = view->window->w / 2;
	y = view->window->h / 2;

	lock = !lock;
	if(!lock){
		SDL_WarpMouse(x,y);
	}
	return lock;
}

/** Return cursor lock status. */
bool Cursor::isLocked(){
	return lock;
}

/** Draw the cursor on the screen.  This is done in 2D mode.
 * The cursor should get several different modes, so this will obviously 
 * have to expand.
 *
 * This should always be the last 2D drawing function called, so that the
 * cursor is on top.
 */
void Cursor::draw(){
	glBindTexture(GL_TEXTURE_2D,glNames[mode]);
	glBegin(GL_QUADS);
// 	if(lock)
// 		glColor4f(1,1,1,0.5);
// 	else
// 		glColor4f(1,1,1,1);
	glTexCoord2f(cursor_coords[mode][0],cursor_coords[mode][3]);
	glVertex2i(x,y);

	glTexCoord2f(cursor_coords[mode][1],cursor_coords[mode][3]);
	glVertex2i(x+CURSOR_SIZE,y);

	glTexCoord2f(cursor_coords[mode][1],cursor_coords[mode][2]);
	glVertex2i(x+CURSOR_SIZE,y-CURSOR_SIZE);

	glTexCoord2f(cursor_coords[mode][0],cursor_coords[mode][2]);
	glVertex2i(x, y-CURSOR_SIZE);


	
	glEnd();
}
