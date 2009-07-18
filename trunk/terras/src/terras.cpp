/** @file terras.cpp
 * Main function and other important initialization functions.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#include <iostream>
#include <stdio.h>

#include "terras.h"
#include "model.h"
#include "node.h"


#ifndef DEBUG
/** Entry point for terras. */
int main(int argc, char **argv){
	Model *model = new Model(argv[0], "data/terraslogic.py");

	return 0;
}

#else

/** Unit test entry point for terras. */
int main(int argc, char **argv){
	Node *node = new Node(std::string("node1"));
	node->render();
	node->handleClick(50, 21);
	node->ready();
	node->unready();
}
#endif


