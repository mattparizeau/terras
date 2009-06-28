


/** Stores filenames for a cubemap. */
struct cubemap_t{
	std::string filenames[6];
	GLuint glNames[6];
	GLfloat coords[6][4];
};

/** A node in the game, which represents a possible position of the player.
 */
class TerraNode{
	public:
		TerraNode(YAML::Node& doc, TerraModel *model);
		~TerraNode();
		void ready();
		void unready();
		bool isReady();

		const std::string getId();
	private:
		std::string id;
// 		GLuint textures[6];
// 		GLfloat coords[6][4];
		cubemap_t imagemap;
		bool _ready;
};

