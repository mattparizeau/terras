
class TerraView;
class TerraController;

class TerraModel{
	public:
		TerraModel();
		~TerraModel();

		void parseConfig();
		void parseConfig(const char *fileName);
		void setView(TerraView *newView);
		void setController(TerraController *newController);
	protected:

	private:
		TerraView *view;
		TerraController *controller;
};