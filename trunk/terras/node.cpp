#include <fstream>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "controller.h"
#include "view.h"
#include "model.h"
#include "node.h"
#include "sdltextures.h"

/** Temporary constructor.  I'm hardcoding names of image files for now. */
TerraNode::TerraNode(){
	int i;
	char *filename;
	for(i = 0; i < 6; i++){
		//filename = malloc(sizeof(char) * 20);
		
	}
}

/** Free allocated memory from the object's construction. */
TerraNode::~TerraNode(){
	int i;
	unready();
	for(i = 0; i < 6; i++){
		free(filenames[i]);
	}
}

/** Load image files and otherwise make this node ready to display. 
 */
void TerraNode::ready(){
	int i;
	SDL_Surface *img;

	if(_ready) return;

	for(i = 0; i < 6; i++){
		img = IMG_Load(filenames[i]);
		if(!img) {
			printf("IMG_Load: %s\n", IMG_GetError());
		}
		textures[i] = SDL_GL_LoadTexture(img, coords[i]);
	}
	_ready = true;
}

/** Unload image files from GPU memory */
void TerraNode::unready(){
	if(!_ready) return;
	glDeleteTextures(6,textures);
	
	_ready = false;
}

