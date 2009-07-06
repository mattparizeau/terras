/** @file terras.cpp
 * Main function definition and other useful tidbits.
 * @author Peter Hokanson
 */
#include <iostream>
#include <vector>
#include <map>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "types.h"
#include "model.h"
#include "controller.h"
#include "view.h"


// Keydown booleans
bool key[321];
// Process pending events

/** Entry into the MVC setup. */
int main(int argc, char **argv) {
	Controller *controller = new Controller();
	Model *model = new Model();
	View *view = new View();

	printf("Starting terras...\n");

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf( stderr, "SDL Video initialization failed: %s\n",
			SDL_GetError() );
		exit(1);
	}

	controller->setView(view);
	view->setController(controller);
	controller->setModel(model);
	model->setController(controller);


	
	//view->currNode = model->nodes.front();
	model->parseConfig();

	view->init();
	view->initGL();

	controller->setCurrentNode(model->getStartNode());
	controller->run();
}
