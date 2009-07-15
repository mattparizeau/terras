#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "sdltextures.h"

/** @file sdltextures.cpp
 * SDL utility functions.
 */

/* Quick utility function for texture creation */
inline int base2(int input) {
	int value = 1;
	while (value < input) {
		value <<= 1;
	}
	return value;
}

/** Load an OpenGL texture from a filename. */
GLuint SDL_GL_LoadTextureFile(const char *fileName, GLfloat *texcoord) {
	SDL_Surface *img;
	GLuint id;

	img = IMG_Load(fileName);
	if(!img) {
		printf("SDL_GL_LoadTextureFile: %s\n", IMG_GetError());
	}
	id = SDL_GL_LoadTexture(img, texcoord);
	SDL_FreeSurface(img);
	return id;
}

/** Load an OpenGL texture from an SDL surface. */
GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord) {
	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	/* Use the surface width and height expanded to powers of 2 */
	w = base2(surface->w);
	h = base2(surface->h);
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)surface->w / w;	/* Max X */
	texcoord[3] = (GLfloat)surface->h / h;	/* Max Y */

	image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF, 
			0x0000FF00, 
			0x00FF0000, 
			0xFF000000
#else
			0xFF000000,
			0x00FF0000, 
			0x0000FF00, 
			0x000000FF
#endif
		       );
	if ( image == NULL ) {
		return 0;
	}

	/* Save the alpha blending attributes */
	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = surface->format->alpha;
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, 0, 0);
	}

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, w, h,
// 											GL_RGBA, GL_UNSIGNED_BYTE, image->pixels );
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     w, h,
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     image->pixels);
	SDL_FreeSurface(image); /* No longer needed */

	return texture;
}
