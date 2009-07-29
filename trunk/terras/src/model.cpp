#include "terras.h"
#include "model.h"
#include "node.h"
#include "yaml.h"


/** Create a model with the given executable name. */
Model::Model(char *argv0){
	currNode = NULL;

	Py_SetProgramName(argv0);
	Py_Initialize();

	/* Initialize global and local dictionaries */
	initterras();
	pmain = PyImport_AddModule("__main__");
	pglobals = PyModule_GetDict(pmain);

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
/** Set the current node. */
void Model::setCurrentNode(Node *node){
	std::cout << "Setting current node to " << node->getId() << std::endl;
	currNode = node;
}
/** Set the current node. */
void Model::setCurrentNode(std::string id){
	std::cout << "Setting current node to " << id << std::endl;
	currNode = nodes[id];
}
/** Get the current node. */
Node *Model::getCurrentNode(){
	return currNode;
}

/** Render the current node. */
void Model::render(){
	currNode->render();
}

/** Run a Python script from a filename. */
void Model::runScript(std::string fileName){
	FILE *f = fopen(fileName.c_str(),"r");
	assert(f);
	if(!PyRun_FileEx(f, fileName.c_str(), Py_file_input, pglobals, pglobals, 1)){
		// Exception raised
		PyErr_PrintEx(0);
		printf("Exception raised in Python script: %s!\n", fileName.c_str());
	}
}

/** Load node information from a YAML file.  For the moment, it might
 * be best to farm this out to Python, as pyyaml works pretty well. */
void Model::loadYAML(std::string fileName){
	std::ifstream fin(fileName.c_str());
//	YAML::Parser parser(fin);

// 	while(parser) {
// 		YAML::Node doc;
// 		parser.GetNextDocument(doc);
// 	}

	return;
}

void Model::writeYAML(std::string fileName){
	//std::ofstream fout(fileName);
}
