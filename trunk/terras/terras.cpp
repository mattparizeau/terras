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
	Model *model = new Model(controller);
	View *view = new View(controller, model);

	printf("Starting terras...\n");
	/* Initialize Controller */
	controller->setView(view);
	controller->setModel(model);

	controller->setCurrentNode(model->getStartNode());
	controller->run();
}
