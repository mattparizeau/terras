
#define FILE_CURSOR_POINTER "data/cursors/fwd.png"

/** Represents the cursor, and is able to handle motion and multiple modes. 
 */
class TerraCursor{
	public:
		TerraCursor(TerraView *newView);
		~TerraCursor();
		
		void setMode(cursor_mode_t newMode);
		void setCoords(int x1,int y1);
		void draw();
		bool toggleLock();
		bool isLocked();
	private:
		TerraView *view;

		int x,y;
		bool lock;

		cursor_mode_t mode;
		GLuint glNames[NUM_CURSORS];
		GLfloat cursor_coords[NUM_CURSORS][4];
};