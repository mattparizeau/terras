#include "terras.h"
#include "model.h"
#include "node.h"
#include "callback.h"

/** Create a callback associated with a given node. */
Callback::Callback(Node *parentNode){
	node = parentNode;
	node->addCallback(this);
	target = NULL;
	code = "";
}

/** Call this callback (virtual), */
void Callback::call(){
	std::cout << "Calling callback for node " << node->getId() << std::endl;
	model->callPython(code.c_str());
	if(target != NULL)
		model->setCurrentNode(target);
}

void Callback::setCode(std::string newCode){
	code = newCode;
}

void Callback::setTarget(std::string targetId){
	target = model->getNode(targetId);
}

void Callback::setTarget(Node *ptarget){
	target = ptarget;
}

