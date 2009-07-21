#include "terras.h"
#include "model.h"
#include "node.h"

/** Create a model with the given executable name. */
Model::Model(char *argv0, const char *fileName){
	FILE *f = fopen(fileName,"r");
	assert(f);

	Py_SetProgramName(argv0);
	Py_Initialize();

	/* Initialize global and local dictionaries */
	pmain = PyImport_AddModule("__main__");
	pglobals = PyModule_GetDict(pmain);

	/* Run our initialization file */
	if(!PyRun_FileEx(f, fileName, Py_file_input, pglobals, pglobals, 1)){
		// Exception raised
		printf("Exception raised in Python script: %s!\n", fileName);
	}
	
}

/** Destructor for the model, which terminates the Python process and decrements
 * the appropriate reference counts. */
Model::~Model(){
	/* Decrement local variables */
	Py_DECREF(pglobals);

	Py_Finalize();
}

/** Call a Python string with a consistent context from our initialization in
 * terms of global and local dictionaries. */
void Model::callPython(const char *code){
	PyObject *pObj;
	pObj = PyRun_String(code, Py_eval_input, pglobals, pglobals);
}

/** Add a node to the directed graph. */
void Model::addNode(std::string id, Node *node){
	nodes[id] = node;
}
/** Get a node by it's ID. */
Node *Model::getNode(std::string id){
	return nodes[id];
}
