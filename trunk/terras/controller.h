
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
class Controller{
	public:
		/* Initialization */
		Controller();
		~Controller();
		/* Main loop */
		void run();

		/* Setters */
		void setView(View *newView);
		void setModel(Model *newModel);
		void setCurrentNode(Node *newNode);

		/* Public state information */
		GameConfig config;
		GameStatus state;
	protected:
		bool events();

		View *view;
		Model *model;
		Node *currNode;
	private:
		bool key[321];
};