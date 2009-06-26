
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

};

/** Controller for the MVC Pattern. */
class TerraController{
	public:
		TerraController();
		~TerraController();
		GameStatus status;
		void run();

		void setView(TerraView *newView);
	protected:
		bool events();

		TerraView *view;
	private:
		bool key[321];
		
		GameConfig config;
};