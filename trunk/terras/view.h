#define window_width  640
#define window_height 480
#define FOV 45

class TerraController;

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
	protected:
		TerraController *controller;
		SDL_Surface *window;

		GLfloat texcoords[4];
		GLuint texture;

		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
};