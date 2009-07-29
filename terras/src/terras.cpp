/** @file terras.cpp
 * Main function and other important initialization functions.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#include "terras.h"
#include "model.h"

/** Pointer to the global model object. */
Model *model;
/** Global pointer to the current node (it's used in a lot of places). */
Node *currNode;

#ifndef DEBUG
/** Entry point for terras. */
//int main(int argc, char **argv){
int main(){
	model = new Model(argv[0]);

	return 0;
}

#else

#include "node.h"
#include "callback.h"
#include "cubenode.h"

static void testModel(char *argv0);

/** Testing entry point for terras. */
int main(int argc, char **argv){
	testModel(argv[0]);
}

static void testModel(char *argv0){
	model = new Model(argv0);
	model->runScript("data/testlogic.py");

	Callback *cb = new Callback(model->getNode("hello"));
	cb->setCode("print \"Python Callback successful: x =\",x");
	//cb->setTarget("node2");
	cb->call();
	//assert(model->getCurrentNode()->getId() == "node2");

	std::cout << "Done" << std::endl;
}
#endif


