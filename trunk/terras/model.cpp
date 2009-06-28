//#include <mbstring.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <yaml.h>

#include "view.h"
#include "controller.h"
#include "model.h"
#include "node.h"

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
		if(key == "nodefile"){
			std::string nodeFileName;
			it.second() >> nodeFileName;
			parseNodes(nodeFileName.c_str());
		}
	}
}

/** Parse a YAML node file.
 */
void TerraModel::parseNodes(const char *fileName){
	std::ifstream fin(fileName);
	YAML::Parser parser(fin);
	while(parser){
		YAML::Node doc;
		parser.GetNextDocument(doc);
		TerraNode *node = new TerraNode(doc,this);
		//nodes[node->getId()] = node;
		nodes.push_back(node);
	}
}


void TerraModel::setController(TerraController *newController){
	controller = newController;
}