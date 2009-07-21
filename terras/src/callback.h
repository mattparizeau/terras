
#ifndef __CALLBACK_H__
#define __CALLBACK_H__
/** Virtually handles hotspots within nodes and the associated callbacks to 
 * Python. */
class Callback{
	public:
		Callback(Node *parentNode);
		//virtual bool testActivate(int x, int y);
		virtual void call();
	private:
		Node *node; /**< Node associated with this callback. */
};

/** Handles callbacks specifically to Python. */
class PythonCallback: public Callback{
	public:
		PythonCallback(Node *parentNode);

// 		PythonCallback* create() const { return new Foo (); }

		void setCode(std::string newCode);
		void call();
	private:
		std::string code;
};

#endif
