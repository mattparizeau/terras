#define CURSOR_SIZE 17

class TerraView{
	public:
		/* Friend classes */
		friend class TerraCursor;
		/* Initialization */
		TerraView();
		~TerraView();
		void init();
		void initGL();

		/* Rendering functions */
		void draw();
		void draw2D();
		void draw3D();

		/* External callback handlers */
		void setCurrentNode(TerraNode *currNode);
		int grabMouse();
		void adjustAngle(GLdouble x, GLdouble y);

		/* Getters and Setters */
		void setController(TerraController *c);
		TerraCursor *getCursor();

	private:
		/* Relevant external data structures */
		TerraController *controller;
		TerraNode *currNode;
		TerraCursor *cursor;
		SDL_Surface *window;

		/* Graphics state information */
		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
// 		GLuint cursor;
// 		GLfloat cursor_coords[4];
};