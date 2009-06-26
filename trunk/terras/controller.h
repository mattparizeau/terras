
class TerraView;
class TerraModel;

/** Stores the status of the game within the controller.
 */
struct GameStatus{
	
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

		void run();

		void setView(TerraView *newView);
	protected:
		bool events();

		TerraView *view;
	private:
		bool key[321];
		GameStatus status;
		GameConfig config;
};