

class View{
	public:
		/* Friend classes */
		friend class Cursor;
		/* Initialization */
		View();
		~View();
		void init();
		void initGL();

		/* Rendering functions */
		void draw();
		void draw2D();
		void draw3D();

		/* External callback handlers */
		void setCurrentNode(Node *currNode);
		int grabMouse();
		void adjustAngle(GLdouble x, GLdouble y);

		/* Getters and Setters */
		void setController(Controller *c);
		Cursor *getCursor();

	private:
		/* Relevant external data structures */
		Controller *controller;
		Node *currNode;
		Cursor *cursor;
		SDL_Surface *window;

		/* Graphics state information */
		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
// 		GLuint cursor;
// 		GLfloat cursor_coords[4];
};