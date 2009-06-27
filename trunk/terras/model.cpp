//#include <mbstring.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <yaml.h>

#include "view.h"
#include "controller.h"
#include "model.h"

TerraModel::TerraModel(){

}

TerraModel::~TerraModel(){

}

/** Utility function to compare scalars and strings */
inline bool yamlcmp(yaml_event_t evt,const char * str){
	//assert(evt.type == YAML_SCALAR_EVENT);
	return ( memcmp(evt.data.scalar.value,str,evt.data.scalar.length) == 0);
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
	yaml_parser_t parser;
	yaml_event_t event, value;
	FILE *configFile;
	
	configFile = fopen(fileName,"r");
	if(!yaml_parser_initialize(&parser)){
		printf("YAML: PARSE FAILED\n");
	};
	yaml_parser_set_input_file(&parser, configFile);
	
	/* Read the event sequence. */
	while(1){
		
		/* Get the next event. */
		if (!yaml_parser_parse(&parser, &event)){
			printf("YAML Parse error\n");
			break;
		}
		if(event.type == YAML_MAPPING_START_EVENT)
			printf("YAML: Starting mapping\n");
		if(event.type == YAML_SCALAR_EVENT){
			yaml_parser_parse(&parser, &value);
			if(yamlcmp(event,"width")){
				controller->config.width = (int) strtol((char*)event.data.scalar.value,NULL,10);
				printf("Set width to %d", controller->config.width);
			}
			if(yamlcmp(event,"height")){
				controller->config.height = (int) strtol((char*)event.data.scalar.value,NULL,10);
				printf("Set width to %d", controller->config.height);
			}
	
			printf("%s\n", value.data.scalar.value);
			
			yaml_event_delete(&value);
		}

		if(event.type == YAML_STREAM_END_EVENT) break;

		/* The application is responsible for destroying the event object. */
		yaml_event_delete(&event);
	}
	yaml_parser_delete(&parser);
	fclose(configFile);

	return;
}


void TerraModel::setController(TerraController *newController){
	controller = newController;
}