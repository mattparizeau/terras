
/** The view class in the MVC pattern.  Specifically, this deals with all code
 * relating to output.  This includes OpenGL, and will eventually include
 * SDL_mixer music and sound capability.
 */
class View{
	public:
		/* Friend classes */
		friend class Cursor;
		/* Initialization */
		View(Controller *newController, Model *newModel);
		~View();
		

		/* Rendering functions */
		void draw();
		void draw2D();
		void draw3D();

		/* External callback handlers */
		void setCurrentNode(Node *currNode);
		int grabMouse();
		void changeAngle(GLdouble x, GLdouble y);

		/* Getters and Setters */
		void setController(Controller *c);
		Cursor *getCursor();

	private:
		/* Initialization functions */
		void init();
		void initGL();

		/* Relevant external data structures */
		Controller *controller;
		Model *model;
		Node *currNode;
		Cursor *cursor;
		SDL_Surface *window;
		hotspot_t *currSpot;

		/* Graphics state information */
		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
// 		GLuint cursor;
// 		GLfloat cursor_coords[4];
};