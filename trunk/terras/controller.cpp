#include <fstream>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "view.h"
#include "controller.h"


TerraController::TerraController(){
	/* Initialize arrays */
	memset(&key,0,321 * sizeof(bool));
	/* Set configuration to defaults */
	config.width = 640;
	config.height = 480;
	config.fov = 45;

	return;
}

/** Start the main event loop.
 * @author Peter Hokanson
 */
void TerraController::run() {
	while( events() ) {
		view->draw();
		SDL_Delay(30);
	}
}

/** Process SDL events.  This should probably change to a 
 * @author Peter Hokanson
 */
bool TerraController::events() {
	int deltax,deltay;
	SDL_Event event;
	Uint8 mouseKeys;

	if(SDL_WaitEvent(&event) ) {
		switch( event.type ) {
			case SDL_KEYDOWN : key[ event.key.keysym.sym ]=true ;   break;
			case SDL_KEYUP   : key[ event.key.keysym.sym ]=false;   break;
			case SDL_MOUSEBUTTONDOWN:
				//SDL_WM_GrabInput(SDL_GRAB_ON);
				break;
			case SDL_QUIT    : return false; break;
		}
	}
	if( key[SDLK_RIGHT] ) {view->adjustAngle( 1, 0);}
	if( key[SDLK_LEFT ] ) {view->adjustAngle(-1, 0);}
	if( key[SDLK_UP   ] ) {view->adjustAngle( 0,-1);}
	if( key[SDLK_DOWN ] ) {view->adjustAngle( 0, 1);}

	/* Mouse movement */
	mouseKeys = SDL_GetRelativeMouseState(&deltax, &deltay);
	view->adjustAngle((double)deltax,(double)deltay);

	return true;
}

// GET / SET FUNCTIONS

void TerraController::setView(TerraView *newView){
	view = newView;
}

void TerraController::setModel(TerraModel *newModel){
	model = newModel;
}