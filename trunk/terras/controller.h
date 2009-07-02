
/** Stores the status of the game within the controller.
 */
struct GameStatus{
	int videoFlags;
	bool paused;
	const SDL_VideoInfo *videoInfo;
	bool keys_captured;
};

/** Configuration information.
 */
struct GameConfig{
	int width; /**< Screen width */
	int height; /**< Screen height */
	int fov; /**< Cube view angle */
	std::string title; /**< Window Title */
	bool fullscreen; /**< Lock to fullscreen */
	float sensitivity; /**< Mouse sensitivity */
};

/** Controller for the MVC Pattern. */
class TerraController{
	public:
		/* Initialization */
		TerraController();
		~TerraController();
		/* Main loop */
		void run();

		/* Setters */
		void setView(TerraView *newView);
		void setModel(TerraModel *newModel);
		void setCurrentNode(TerraNode *newNode);

		/* Public state information */
		GameConfig config;
		GameStatus state;
	protected:
		bool events();

		TerraView *view;
		TerraModel *model;
		TerraNode *currNode;
	private:
		bool key[321];
};