#include "terras.h"
#include "model.h"
#include "callback.h"
#include "node.h"
#include "cubenode.h"

/** Constructor. */
CubeNode::CubeNode(std::string nodeId) : Node(nodeId){ }

/** Handle a click operation.  In a true implementation, this should determine
 * the correct callback, if any.
 */
void CubeNode::handleClick(int x, int y){
	std::cout << "Node " << id << " recieved click at " << x << " " << y << std::endl;
}

/** Prepare this node for rendering by incrementing its reference count.  A
 * true implementation will load the appropriate textures into OpenGL and
 * otherwise prepare for this node to become the current node quickly.
 */
void CubeNode::ready(){
	refCount++;
	if(refCount == 1){
		std::cout << "Readying node: " << id << std::endl;
	}
}

/** Deallocate resources for this node when it is no longer in focus.  This
 * decrements the reference count as a test implementation. */
void CubeNode::unready(){
	refCount--;
	if(refCount == 0){
		std::cout << "Unreadying node: " << id << std::endl;
	}
	if(refCount < 0) refCount = 0;
}


void CubeNode::render(){
	std::cout << "Rendering 3D node " << id << std::endl;
}
