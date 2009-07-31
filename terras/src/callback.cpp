#include "terras.h"
#include "model.h"
#include "node.h"
#include "callback.h"

/** Create a callback associated with a given node. */
Callback::Callback(Node *parentNode){
	node = parentNode;
	node->addCallback(this);
	targetId = std::string("");
	code = std::string("");
}

/** Create a callback associated with a node id. */
Callback::Callback(std::string id){
	node = model->getNode(id);
	node->addCallback(this);
	targetId = std::string("");
	code = std::string("");
}

/** Call this callback (virtual), */
void Callback::call(){
	std::cout << "Calling callback for node " << node->getId() << std::endl;
	model->callPython(code.c_str());
	if(targetId != "")
		model->setCurrentNode(targetId);
}

/** Set the code that will be called by this callback. */
void Callback::setCode(std::string newCode){
	code = std::string(newCode);
}

/** Set the node target of this callback.  When activated, the current node will
 * switch to the target node. This takes a string */
void Callback::setTarget(std::string id){
	targetId = id; 
}

