#include <fstream>
#include <iostream>
#include <vector>
#include <yaml.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "types.h"
#include "view.h"
#include "model.h"
#include "node.h"
#include "controller.h"


TerraController::TerraController(){
	/* Initialize arrays */
	memset(&key,0,321 * sizeof(bool));
	/* Set configuration to defaults */
	config.width = 640;
	config.height = 480;
	config.fov = 45;
	config.sensitivity = 1.0;
	
	/* Set initial state */
	state.mouse_free = false;

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
				if(event.button.button == SDL_BUTTON_RIGHT && 
					event.button.state == SDL_PRESSED){
					if(state.mouse_free == true){SDL_ShowCursor(SDL_DISABLE);}
					else{SDL_ShowCursor(SDL_ENABLE);}
					state.mouse_free = !state.mouse_free;
				}
				break;
			case SDL_QUIT    : return false; break;
		}
	}
	if( key[SDLK_RIGHT] ) {view->adjustAngle( 1, 0);}
	if( key[SDLK_LEFT ] ) {view->adjustAngle(-1, 0);}
	if( key[SDLK_UP   ] ) {view->adjustAngle( 0,-1);}
	if( key[SDLK_DOWN ] ) {view->adjustAngle( 0, 1);}
	if( key[SDLK_q    ] ) return false;

	/* Mouse movement */
	mouseKeys = SDL_GetRelativeMouseState(&deltax, &deltay);
	if(!state.mouse_free){
		view->adjustAngle((double)deltax,(double)deltay);
	}

	return true;
}

// GET / SET FUNCTIONS

void TerraController::setView(TerraView *newView){
	view = newView;
}

void TerraController::setModel(TerraModel *newModel){
	model = newModel;
}

void TerraController::setCurrentNode(TerraNode *newNode){
	/* Ensure that the node is ready to be loaded. */
	newNode->ready();

	/* Register the node in the correct places */
	currNode = newNode;
	view->setCurrentNode(newNode);
	model->setCurrentNode(newNode);
}