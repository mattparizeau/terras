#include "terras.h"
#include "model.h"
#include "node.h"

/** Create a model with the given executable name. */
Model::Model(char *argv0, const char *fileName){
	FILE *f = fopen(fileName,"r");
	assert(f);

	/* Initialize global and local dictionaries */
	pglobals = PyDict_New();
	plocals = PyDict_New();

	Py_SetProgramName(argv0);
	Py_Initialize();

	if(PyImport_ImportModule("sys"))
		printf("Loaded 'sys'\n");

	if(!PyRun_FileEx(f, fileName, Py_file_input, pglobals, plocals, 1)){
		// Exception raised
		printf("Exception raised!\n");
	}
	
}

/** Destructor for the model, which terminates the Python process and decrements
 * the appropriate reference counts. */
Model::~Model(){
	/* Decrement local variables */
	Py_DECREF(pglobals);
	Py_DECREF(plocals);

	Py_Finalize();
}

/** Add a node to the directed graph. */
void Model::addNode(std::string id, Node *node){
	nodes[id] = node;
}
/** Get a node by it's ID. */
Node *Model::getNode(std::string id){
	return nodes[id];
}