/** @file cubenode.h
 * Cube node that uses OpenGL to render an immersive skybox as a node. */

#ifndef __CUBENODE_H__
#define __CUBENODE_H__

/** A node which is rendered as a three-dimensional cube, which is textured
 * such that it appears as a seamless node like those in Myst III or Myst IV. */
class CubeNode: private Node{
	public:
		CubeNode(std::string nodeId);
		//void setId(std::string nodeId);

		void render();
		void handleClick(int x, int y);
		void ready();
		void unready();
// 		class CubeCallback: private Callback{
// 			
// 		};
	private:
		std::string id;
		int refCount;
};

#endif