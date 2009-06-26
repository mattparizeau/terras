#define window_width  640
#define window_height 480

class TerraController;

class TerraView{
	public:
		TerraView();
		~TerraView();
		void adjustAngle(GLdouble x, GLdouble y);
		void draw();

	protected:
		TerraController *controller;

		GLdouble xangle, yangle;
		int width, height;
		const SDL_VideoInfo *info;
		int vidFlags, bpp;
};