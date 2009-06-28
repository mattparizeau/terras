#define window_width  160
#define window_height 120
#define FOV 45

class TerraView{
	public:
		TerraView();
		~TerraView();
		void adjustAngle(GLdouble x, GLdouble y);
		void draw();
		void init();
		void initGL();

		void loadTextures();

		void setController(TerraController *c);

		int grabMouse();
	protected:
		TerraController *controller;
		SDL_Surface *window;

		GLfloat texcoords[6][4];
		GLuint texture[6];

		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
};