/** @file model.h
 * Data structures and prototypes used for the backend of the Terras engine.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#ifndef __MODEL_H__
#define __MODEL_H__
#include <boost/python/detail/wrap_python.hpp>

/** Initialize the Node object within embedded Python. */
extern "C" void initterras();

/** Callback to be exposed to Boost::Python. */
void setNode(std::string id);

/** The Model in our pattern, which in this case uses Python bindings to
 * handle node creation, game logic, and other such things.
 */
class Model{
	public:
		/* Constructors and Destructors */
		Model(char *argv0);
		~Model();
		/* Python Interface */
		void runScript(std::string fileName);
		void callPython(const char *code);
		void loadYAML(std::string fileName);
		void writeYAML(std::string fileName);

		/* Node functions */
		void addNode(std::string id, Node *node);
		Node *getNode(std::string id);
		void setCurrentNode(Node *node);
		void setCurrentNode(std::string id);
		Node *getCurrentNode();
		void render();

	private:
		PyObject *pmain, *pglobals; //*plocals, *pmain;
		std::map<std::string, Node*> nodes;
		Node *currNode;
};


#endif