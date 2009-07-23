/** @file model.h
 * Data structures and prototypes used for the backend of the Terras engine.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#ifndef __MODEL_H__
#define __MODEL_H__
#include <boost/python/detail/wrap_python.hpp>

/** The Model in our pattern, which in this case uses Python bindings to
 * handle node creation, game logic, and other such things.
 */
class Model{
	public:
		/* Constructors and Destructors */
		Model(char *argv0, const char *fileName);
		~Model();
		/* Python Interface */
		void callPython(const char *code);

		/* Node functions */
		void addNode(std::string id, Node *node);
		Node *getNode(std::string id);
		void setCurrentNode(Node *node);
	private:
		PyObject *pmain, *pglobals; //*plocals, *pmain;
		std::map<std::string, Node*> nodes;
		Node *currNode;
};


#endif