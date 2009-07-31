/** @file pythonlib.cpp
 * Definitions of functions that can be called back from Python, as well as the
 * boost templating for the relevant Python module, 'terras'.
 */

#include "terras.h"
#include "model.h"
#include "callback.h"
#include "node.h"

using namespace boost::python;

/** Set the node that is currently in focus. */
static void setNode(std::string id){
	model->setCurrentNode(id);
}


BOOST_PYTHON_MODULE(terras){
	class_<Node>("Node", init<std::string>())
		.def("getId", &Node::getId)
	;
	class_<Callback>("Callback", init<std::string>())
		.def("call",&Callback::call)
		.def("setCode",&Callback::setCode)
		.def("setTarget",&Callback::setTarget)
	;
	def("setNode", setNode);
}



