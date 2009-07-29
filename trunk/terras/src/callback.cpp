#include "terras.h"
#include "model.h"
#include "node.h"
#include "callback.h"

/** Create a callback associated with a given node. */
Callback::Callback(Node *parentNode){
	node = parentNode;
	node->addCallback(this);
	target = NULL;
	code = std::string("");
}

/** Call this callback (virtual), */
void Callback::call(){
	std::cout << "Calling callback for node " << node->getId() << std::endl;
	model->callPython(code.c_str());
	if(target != NULL)
		model->setCurrentNode(target);
}

/** Set the code that will be called by this callback. */
void Callback::setCode(std::string newCode){
	code = std::string(newCode);
}

/** Set the node target of this callback.  When activated, the current node will
 * switch to the target node. This takes a string */
void Callback::setTarget(std::string targetId){
	target = model->getNode(targetId);
}

/** Set the node target with a node pointer. */
void Callback::setTarget(Node *ptarget){
	target = ptarget;
}

