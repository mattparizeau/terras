/** @file node.h
 * We seek to build a rather generic framework for a variety of nodes that
 * could be useful in node-based adventure games.  Myst is not that fundamentally 
 * different from, say, Space Quest, or other text-based adventure games.
 * @author Peter Hokanson
 */

#ifndef __NODE_H__
#define __NODE_H__

/** Represents a generic node within our directed graph.  This should be
 * abstract, and not generally used specifically, except perhaps for testing. */
class Node{
	public:
		Node(std::string nodeId);
		//~Node();
		virtual void render();
		virtual void handleClick(int x, int y);
		virtual void ready();
		virtual void unready();
		std::string getId();
	private:
		std::string id;
		int refCount;
};

/** A node which is rendered as a three-dimensional cube, which is textured
 * such that it appears as a seamless node like those in Myst III or Myst IV. */
class CubeNode: public Node{
	public:
	
	private:
		
};

#endif