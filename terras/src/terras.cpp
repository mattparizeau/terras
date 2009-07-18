/** @file terras.cpp
 * Main function and other important initialization functions.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#include "terras.h"
#include "model.h"
#include "node.h"
#include "cubenode.h"

/** Pointer to the global model object. */
Model *model;
/** Global pointer to the current node (it's used in a lot of places). */
Node *currNode;

#ifndef DEBUG
/** Entry point for terras. */
//int main(int argc, char **argv){
int main(){
	model = new Model(argv[0], "data/terraslogic.py");

	return 0;
}

#else

/** Testing entry point for terras. */
//int main(int argc, char **argv){
int main(int argc, char **argv){
	model = new Model(argv[0], "data/terraslogic.py");
	Node *node = new Node(std::string("node1"));
	node->render();
	node->handleClick(50, 21);
	node->ready();
	node->unready();
}
#endif


