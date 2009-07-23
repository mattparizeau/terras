
#ifndef __CALLBACK_H__
#define __CALLBACK_H__
/** Virtually handles hotspots within nodes and the associated callbacks to 
 * Python. */
class Callback{
	public:
		Callback(Node *parentNode);
		//virtual bool testActivate(int x, int y);
		void call();

		void set3dCoords(double alt, double az);
		void setCode(std::string newCode);
		void setTarget(Node *ptarget);
		void setTarget(std::string targetId);
	private:
		Node *node; /**< Node associated with this callback. */
		Node *target; /**< Node to set when this callback is called. */
		std::string code; /**< Code to execute. */
};

/** Handles callbacks specifically to Python. */
// class PythonCallback: public Callback{
// 	public:
// 		PythonCallback(Node *parentNode);
// 
// // 		PythonCallback* create() const { return new Foo (); }
// 
// 		void setCode(std::string newCode);
// 		void call();
// 	private:
// 		std::string code;
// };

/** Handles callbacks that */
// class NodeCallback: public Callback{
// 	public:
// 		NodeCallback(Node *parentNode);
// 		void setTarget(std::string nodeId);
// 		void call();
// 	private:
// 		Node *target;
// };

#endif
