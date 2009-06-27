//#include <mbstring.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <fstream>
#include <iostream>
#include "yaml.h"

#include "view.h"
#include "controller.h"
#include "model.h"

TerraModel::TerraModel(){

}

TerraModel::~TerraModel(){

}

/** We have a default configuration file. */
void TerraModel::parseConfig(){
	parseConfig("test/config.yaml");
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
		std::string key, value;
		it.first() >> key;
		if(key == "height")
			it.second() >> controller->config.height;
		if(key == "width")
			it.second() >> controller->config.width;
		if(key == "fov")
			it.second() >> controller->config.fov;
		if(key == "title")
			it.second() >> controller->config.title;
	}
}


void TerraModel::setController(TerraController *newController){
	controller = newController;
}