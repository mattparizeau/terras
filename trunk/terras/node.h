
/** Orientation for the faces of a cube:
 * North, South, East, West, Up, Down.
 */
enum Orient {N=0,E,S,W,U,D};

/** A node in the game, which represents a possible position of the player.
 */
class TerraNode{
	public:
		TerraNode();
		~TerraNode();
		void ready();
		void unready();
		bool isReady();

	private:
		GLuint textures[6];
		GLfloat coords[6][4];
		char *filenames[6];
		bool _ready;
};

