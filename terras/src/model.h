/** @file model.h
 * Data structures and prototypes used for the backend of the Terras engine.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#ifndef __MODEL_H__
#define __MODEL_H__
#include <Python.h>

class Model{
	public:
		Model(char *argv0, char *fileName);
		~Model();
	private:
		PyObject *globals, *locals;
};


#endif