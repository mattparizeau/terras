#include "terras.h"
#include "view.h"
#include "model.h"
#include "node.h"
#include "yaml.h"



/** Constructor.  This creates a SDL window and sets up OpenGL. */
View::View(){
	height = 480; width = 640;
	initVideo();
}

/** Construct a SDL window with a given width and height. */
View::View(int winWidth, int winHeight){
	width = winWidth; height = winHeight;
	initVideo();
}

/** Initialize the SDL Video subsystem. */
void View::initVideo(){
	printf("Initializing SDL Video subsystem\n");
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "SDL Video initialization failed: %s\n", SDL_GetError());
		exit(1);
	}

	info = SDL_GetVideoInfo();      
	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
	if (info->hw_available) {vidFlags |= SDL_HWSURFACE;}
	else {vidFlags |= SDL_SWSURFACE;}
	bpp = info->vfmt->BitsPerPixel;

	/* Not creating the window just yet -- I'm going to work on
	 * the controller first. */
	printf("Initializing SDL to %dx%dx%d\n", width, height, bpp);
	window = SDL_SetVideoMode(width, height, bpp, vidFlags);

	if(!window){
		SDL_Quit();
		exit(1);
	}

	SDL_WM_SetCaption("hello", NULL);

	
}

/** Render the scene. */
void View::render(){
	// TODO: Render with OpenGL
}


