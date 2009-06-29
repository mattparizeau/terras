#include <fstream>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <yaml.h>

#include "types.h"
#include "view.h"
#include "model.h"
#include "node.h"
#include "sdltextures.h"

/** Operator overload to assign a YAML node to a cubemap. */
void operator >> (const YAML::Node& node, cubemap_t& v){
	node[0] >> v.filenames[N];
	node[1] >> v.filenames[E];
	node[2] >> v.filenames[S];
	node[3] >> v.filenames[W];
	node[4] >> v.filenames[U];
	node[5] >> v.filenames[D];
}

/** Construct a node from a given YAML stream.
 *
 */
TerraNode::TerraNode(YAML::Node& doc, TerraModel *model){
	/* Initialize local variables */
	_ready = false;

	/* Read node from YAML file */
	for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
		std::string key;
		it.first() >> key;

		if(key == "id")
			it.second() >> id;
		if(key == "imagemaps"){
			it.second() >> imagemap; 
		}
	}


	std::cout << "Created node: " << id << std::endl;
}

/** Free allocated memory from the object's construction. */
TerraNode::~TerraNode(){
	//int i;
	unready();
}

/** Load image files and otherwise make this node ready to display. 
 */
void TerraNode::ready(){
	int i;
	SDL_Surface *img;

	if(_ready) return;

	for(i = 0; i < 6; i++){
		img = IMG_Load(imagemap.filenames[i].c_str());
		if(!img) {
			printf("IMG_Load: %s\n", IMG_GetError());
		}
		imagemap.glNames[i] = SDL_GL_LoadTexture(img, imagemap.coords[i]);
		SDL_FreeSurface(img);
	}
	_ready = true;
	//std::cout << "Node " << id << " ready." << std::endl;
}

/** Unload image files from GPU memory */
void TerraNode::unready(){
	if(!_ready) return;
	glDeleteTextures(6,imagemap.glNames);
	
	_ready = false;
}

/** Return true if this node is ready, false otherwise. */
bool TerraNode::isReady(){
	return _ready;
}

/** Return a pointer to the imagemap structure. */
cubemap_t *TerraNode::getImagemap(){
	return &imagemap;
}



