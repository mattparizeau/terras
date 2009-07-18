/** @file model.h
 * Data structures and prototypes used for the backend of the Terras engine.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#ifndef __MODEL_H__
#define __MODEL_H__
#include <Python.h>

/** The Model in our pattern, which in this case uses Python bindings to
 * handle node creation, game logic, and other such things.
 */
class Model{
	public:
		Model(char *argv0, const char *fileName);
		~Model();
	private:
		PyObject *pglobals, *plocals;
	
};


#endif