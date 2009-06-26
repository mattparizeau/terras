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
bool events() {
	SDL_Event event;
	if( SDL_PollEvent(&event) ) {
		switch( event.type ) {
			case SDL_KEYDOWN : key[ event.key.keysym.sym ]=true ;   break;
			case SDL_KEYUP   : key[ event.key.keysym.sym ]=false;   break;
			case SDL_QUIT    : return false; break;
		}
	}
return true;
}
void main_loop_function() {
	float angle;
	while( events() ) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(0,0, -10);
		glRotatef(angle, 0, 0, 1);
		glBegin(GL_QUADS);
		glColor3ub(255, 000, 000); glVertex2f(-1,  1);
		glColor3ub(000, 255, 000); glVertex2f( 1,  1);
		glColor3ub(000, 000, 255); glVertex2f( 1, -1);
		glColor3ub(255, 255, 000); glVertex2f(-1, -1);
		glEnd();
		SDL_GL_SwapBuffers();
		// Check keypresses
		if( key[SDLK_RIGHT] ){ angle-=0.5; }
		if( key[SDLK_LEFT ] ){ angle+=0.5; }
	}
}
// Initialze OpenGL perspective matrix
void GL_Setup(int width, int height) {
	
}
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
