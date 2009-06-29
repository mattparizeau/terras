#define CURSOR_SIZE 17

class TerraView{
	public:
		/* Initialization */
		TerraView();
		~TerraView();
		void init();
		void initGL();

		/* Rendering functions */
		void draw();
		void draw2D();
		void draw3D();
		void drawCursor();

		/* External callback handlers */
		void setCurrentNode(TerraNode *currNode);
		int grabMouse();
		void adjustAngle(GLdouble x, GLdouble y);

		/* Getters and Setters */
		void setController(TerraController *c);

	private:
		/* Relevant external data structures */
		TerraController *controller;
		TerraNode *currNode;
		SDL_Surface *window;

		/* Graphics state information */
		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
// 		GLuint cursor;
// 		GLfloat cursor_coords[4];
};