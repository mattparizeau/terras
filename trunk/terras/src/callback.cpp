#include "terras.h"
#include "model.h"
#include "node.h"
#include "callback.h"

/** Create a callback associated with a given node. */
Callback::Callback(Node *parentNode){
	node = parentNode;
	node->addCallback(this);
}

void Callback::call(){
	std::cout << "Calling callback for node " << node->getId() << std::endl;
}

PythonCallback::PythonCallback(Node *parentNode) : Callback(parentNode){
}

void PythonCallback::call(){
	PyRun_SimpleString(code.c_str());
}


void PythonCallback::setCode(std::string newCode){
	code = newCode;
}

