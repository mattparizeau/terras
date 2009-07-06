/** Model in the MVC pattern.  This represents an abstract node graph, and can
 * create it from external files and such.
 */
class Model{
	public:
		/* Initialization */
		Model();
		~Model();

		/* Parsing functions */
		void parseConfig();
		void parseConfig(const char *fileName);
		void parseNodes(const char *fileName);

		/* Setters */
		void setView(View *newView);
		void setController(Controller *newController);
		void setCurrentNode(Node *newNode);
		Node *getStartNode();
		/* This should go private at some point in the future */
		std::vector <Node*> nodes;

	private:
		/* Relevant structures */
		View *view;
		Controller *controller;
		Node *currNode;
		Node *startNode;
		/* Local state */
		std::string currNodeId;
		std::map <std::string, Node*> nodemap;
};