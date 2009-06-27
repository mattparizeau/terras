
class TerraView;
class TerraModel;

/** Stores the status of the game within the controller.
 */
struct GameStatus{
	int videoFlags;
	bool paused;
	const SDL_VideoInfo *videoInfo;
};

/** Configuration information.
 */
struct GameConfig{
	int width; /**< Screen width */
	int height; /**< Screen height */
	int fov; /**< Cube view angle */
	std::string title;
};

/** Controller for the MVC Pattern. */
class TerraController{
	public:
		TerraController();
		~TerraController();
		GameStatus status;
		void run();

		void setView(TerraView *newView);
		void setModel(TerraModel *newModel);
		GameConfig config;

	protected:
		bool events();

		
		TerraView *view;
		TerraModel *model;
	private:
		bool key[321];
		
		
};