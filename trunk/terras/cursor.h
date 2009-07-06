
#define FILE_CURSOR_POINTER "data/cursors/fwd.png"
#define CURSOR_SIZE 64

/** Represents the cursor, and is able to handle motion and multiple modes. 
 */
class Cursor{
	public:
		Cursor(View *newView);
		~Cursor();
		
		void setMode(cursor_mode_t newMode);
		void setCoords(int x1,int y1);
		void draw();
		bool toggleLock();
		bool isLocked();
	private:
		View *view;

		int x,y;
		bool lock;

		cursor_mode_t mode;
		GLuint glNames[NUM_CURSORS];
		GLfloat cursor_coords[NUM_CURSORS][4];
};