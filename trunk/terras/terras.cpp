/** @file terras.cpp
 * Main function definition and other useful tidbits.
 * @author Peter Hokanson
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "controller.h"
#include "view.h"

// Keydown booleans
bool key[321];
// Process pending events

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_VIDEO);

	TerraController *controller = new TerraController();
	TerraView *view = new TerraView();

	controller->setView(view);
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
