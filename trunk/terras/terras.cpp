/** @file terras.cpp
 * Main function definition and other useful tidbits.
 * @author Peter Hokanson
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "model.h"
#include "controller.h"
#include "view.h"


// Keydown booleans
bool key[321];
// Process pending events

int main(int argc, char **argv) {
	TerraController *controller = new TerraController();
	TerraModel *model = new TerraModel();
	TerraView *view = new TerraView();
	

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

	//model->parseConfig();
	view->init();
	view->initGL();
	controller->run();
}

// int main(int argc, char **argv) {
// 	TerraView *view = new TerraView();
// 	TerraController *controller = new TerraController();
// 
// 	controller->setView(view);
// 	controller->run();
// 	
// 
// // 	main_loop_function();
// }
