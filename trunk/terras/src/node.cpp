#include "terras.h"
#include "model.h"
#include "callback.h"
#include "node.h"


/** Create a generic node */
Node::Node(std::string nodeId){
	id = nodeId;
	refCount = 0;
	std::cout << "Created node " << id << std::endl;
	model->addNode(id, this);
}

/** Render a generic node.  This is a simple text-based example. */
void Node::render(){
	std::cout << "Rendering node: " << id << std::endl;
}

/** Handle a click operation.  In a true implementation, this should determine
 * the correct callback, if any.
 */
void Node::handleClick(int x, int y){
	std::cout << "Node " << id << " recieved click at " << x << " " << y <<std::endl;
}

/** Prepare this node for rendering by incrementing its reference count.  A
 * true implementation will load the appropriate textures into OpenGL and
 * otherwise prepare for this node to become the current node quickly.
 */
void Node::ready(){
	refCount++;
	if(refCount == 1){
		std::cout << "Readying node: " << id << std::endl;
	}
}

/** Deallocate resources for this node when it is no longer in focus.  This
 * decrements the reference count as a test implementation. */
void Node::unready(){
	refCount--;
	if(refCount == 0){
		std::cout << "Unreadying node: " << id << std::endl;
	}
	if(refCount < 0) refCount = 0;
}

/** Return the string ID for this node. */
std::string Node::getId(){
	return id;
}

/** Add a callback to this node. */
void Node::addCallback(Callback *cb){
	callbacks.push_back(cb);
}



