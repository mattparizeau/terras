/** Model in the MVC pattern.  This represents an abstract node graph, and can
 * create it from external files and such.
 */
class TerraModel{
	public:
		/* Initialization */
		TerraModel();
		~TerraModel();

		/* Parsing functions */
		void parseConfig();
		void parseConfig(const char *fileName);
		void parseNodes(const char *fileName);

		/* Setters */
		void setView(TerraView *newView);
		void setController(TerraController *newController);
		void setCurrentNode(TerraNode *newNode);
		/* This should go private at some point in the future */
		std::vector <TerraNode*> nodes;

	private:
		/* Relevant structures */
		TerraView *view;
		TerraController *controller;
		TerraNode *currNode;
		/* Local state */
		std::string currNodeId;
};