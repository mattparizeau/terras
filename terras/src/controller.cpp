#include "terras.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include "node.h"
#include "yaml.h"

void Controller::run(){
	while(events()) {
		view->render();
	}
	printf("Recieved quit signal, quitting...\n");
	quit();
}

bool Controller::events(){
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
					/*if(state.mouse_free == true){SDL_ShowCursor(SDL_DISABLE);}
					else{SDL_ShowCursor(SDL_ENABLE);}
					state.mouse_free = !state.mouse_free;*/
					//view->getCursor()->toggleLock();
				}
				break;
			case SDL_QUIT: return false; break;
		}
	}
	if( key[SDLK_q    ] ) return false;

	/* Mouse movement */
	mouseKeys = SDL_GetRelativeMouseState(&deltax, &deltay);
	return true;
}

/** Shut down the game and quit SDL. */
bool Controller::quit(){
	SDL_Quit();
}