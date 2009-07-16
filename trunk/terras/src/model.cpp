

#include <stdio.h>

#include "terras.h"
#include "model.h"

/** Create a model with the given executable name. */
Model::Model(char *argv0, char *fileName){
	FILE *f = fopen(fileName,"r");
	assert(f);

	Py_SetProgramName(argv0);
	Py_Initialize();

	
	PyRun_SimpleString("from time import time,ctime\n"
                     "print 'Today is',ctime(time())\n");
//PyRun_FileExFlags(f, fileName, 0, &globals, &locals, 1, 0);
}

Model::~Model(){

}