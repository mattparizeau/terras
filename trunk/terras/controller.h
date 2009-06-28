
/** Stores the status of the game within the controller.
 */
struct GameStatus{
	int videoFlags;
	bool paused;
	const SDL_VideoInfo *videoInfo;
	bool keys_captured;
	bool mouse_free;
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
		TerraController();
		~TerraController();
		
		void run();

		void setView(TerraView *newView);
		void setModel(TerraModel *newModel);

		GameConfig config;
		GameStatus state;
	protected:
		bool events();

		TerraView *view;
		TerraModel *model;
	private:
		bool key[321];
};