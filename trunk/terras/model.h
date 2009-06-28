
class TerraView;
class TerraController;
class TerraNode;

class TerraModel{
	public:
		TerraModel();
		~TerraModel();

		void parseConfig();
		void parseConfig(const char *fileName);
		void parseNodes(const char *fileName);

		void setView(TerraView *newView);
		void setController(TerraController *newController);
	protected:

	private:
		std::vector <TerraNode*> nodes;
		TerraView *view;
		TerraController *controller;
};