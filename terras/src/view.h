
#ifndef __VIEW_H__
#define __VIEW_H__

/** SDL-based view in our MVC pattern. */
class View{
	public:
		View();
		View(int winWidth, int winHeight);
	private:
		void initVideo();

		SDL_Surface *window;
		/* Graphics state information */
		GLdouble xangle, yangle;
		int width, height, bpp;
		const SDL_VideoInfo *info;
		int vidFlags;

};

#endif /* __VIEW_H__ */