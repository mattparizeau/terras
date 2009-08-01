#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

/** Controller within the MVC pattern. */
class Controller{
	public:
		void run();
	private:
		bool events();
		bool quit();
		bool key[321]; /**< Keyboard signals */
};

#endif /* __CONTROLLER_H__ */