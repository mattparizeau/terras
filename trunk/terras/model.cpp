//#include <mbstring.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <yaml.h>

#include "types.h"
#include "controller.h"
#include "model.h"
#include "node.h"


/** Rather boring constructor */
TerraModel::TerraModel(){

}

/**
 * This actually needs to be expanded in the near future to remove nodes from
 * our graph.
 */
TerraModel::~TerraModel(){

}

/** We have a default configuration file. */
void TerraModel::parseConfig(){
	parseConfig("config.yaml");
}

/** Parse a YAML configuration file.  Such a file is a single mapping of key:
 * value pairs that represent options.  Unset options have defaults.
 * @author Peter Hokanson
 * @author LibYAML
 */
void TerraModel::parseConfig(const char *fileName){
	std::ifstream fin(fileName);
	YAML::Parser parser(fin);
	YAML::Node doc;
	
	printf("Parsing config file %s\n", fileName);
	parser.GetNextDocument(doc);
	for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
		std::string key;
		it.first() >> key;
		if(key == "height")
			it.second() >> controller->config.height;
		if(key == "width")
			it.second() >> controller->config.width;
		if(key == "fov")
			it.second() >> controller->config.fov;
		if(key == "title")
			it.second() >> controller->config.title;
		if(key == "fullscreen")
			it.second() >> controller->config.fullscreen;
		if(key == "sensitivity")
			it.second() >> controller->config.sensitivity;
		if(key == "current_node")
			it.second() >> currNodeId;
		if(key == "nodefile"){
			std::string nodeFileName;
			it.second() >> nodeFileName;
			parseNodes(nodeFileName.c_str());
		}
	}
	std::cout << "Would set current node to " << currNodeId << std::endl;
}

/** Parse a YAML node file.
 */
void TerraModel::parseNodes(const char *fileName){
	std::ifstream fin(fileName);
	YAML::Parser parser(fin);
	//printf("Parsing nodefile %s\n",fileName);
	while(parser){
		YAML::Node doc;
		parser.GetNextDocument(doc);
		TerraNode *node = new TerraNode(doc,this);
		//nodes[node->getId()] = node;
		//node->ready();
		nodes.push_back(node);
	}
}

/** Set controller. */
void TerraModel::setController(TerraController *newController){
	controller = newController;
}
/** Set current node. This should be expanded to preload the appropriate nodes,
 * and unload unused nodes.
 */
void TerraModel::setCurrentNode(TerraNode *newNode){
	currNode = newNode;
}
