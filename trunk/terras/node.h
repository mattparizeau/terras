


/** Stores filenames for a cubemap. */
struct cubemap_t{
	std::string filenames[6];
	GLuint glNames[6];
	GLfloat coords[6][4];
};

/** A node in the game, which represents a possible position of the player.
 */
class Node{
	public:
		/* Initialization and render state */
		Node(YAML::Node& doc, Model *model);
		~Node();
		void ready();
		void unready();
		bool isReady();

		/* Getters and Setters */
		const std::string getId();
		cubemap_t *getImagemap();
		
	private:
		std::string id;
		cubemap_t imagemap;

		bool _ready;
};

