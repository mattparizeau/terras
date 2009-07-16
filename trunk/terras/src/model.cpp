

#include <stdio.h>

#include "terras.h"
#include "model.h"

/** Create a model with the given executable name. */
Model::Model(char *argv0, char *fileName){
	FILE *f = fopen(fileName,"r");
	assert(f);

	/* Initialize global and local dictionaries */
	globals = PyDict_New();
	locals = PyDict_New();

	Py_SetProgramName(argv0);
	Py_Initialize();

//	PyRun_SimpleString("from time import time,ctime\n"
//                     "print 'Today is',ctime(time())\n");
	PyRun_File(f, fileName, Py_file_input, globals, locals);
}

Model::~Model(){
	Py_Finalize();
}