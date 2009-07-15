#include <fstream>
#include <iostream>
#include <math.h>
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

/** Simple square function (not pow). */
inline double sqr(double x){
	return x * x;
}

/** Operator overload to assign a YAML node to a cubemap. */
void operator >> (const YAML::Node& node, cubemap_t& v){
	node[0] >> v.filenames[N];
	node[1] >> v.filenames[E];
	node[2] >> v.filenames[S];
	node[3] >> v.filenames[W];
	node[4] >> v.filenames[U];
	node[5] >> v.filenames[D];
}

/** Converts YAML node into a hotspot. */
// {alt: 0, az: 0, size: 60, call: "MyPythonFunction"}
void operator >> (const YAML::Node &node, hotspot_t &spot){
	std::string type;
	node["call"] >> spot.callback;
	node["alt"] >> spot.alt;
	node["az"] >> spot.az;
	node["size"] >> spot.size;
	node["type"] >> type;
	if(type == "call") 
		spot.type = HOTSPOT_CALLBACK;
	else if(type == "node")
		spot.type = HOTSPOT_NODE;
}

/** Construct a node from a given YAML stream.
 *
 */
Node::Node(YAML::Node& doc, Model *model){
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
		if(key == "hotspots"){
			const YAML::Node &list = it.second();
			std::cout << "Number of spots: " << list.size() << std::endl;
			for(unsigned int i = 0; i < list.size();i++){
				hotspot_t spot;
				list[i] >> spot;
				hotspots.push_back(spot);
				//std::cout << "spot added" << std::endl;
			}
		}
	}

	//std::cout << "Created node: " << id << std::endl;
}

/** Free allocated memory from the object's construction. */
Node::~Node(){
	//int i;
	unready();
}

/** Load image files and otherwise make this node ready to display. 
 */
void Node::ready(){
	int i;

	if(_ready) return;

	for(i = 0; i < 6; i++){
		imagemap.glNames[i] = SDL_GL_LoadTextureFile(imagemap.filenames[i].c_str(),
			imagemap.coords[i]);
	}
	_ready = true;
	//std::cout << "Node " << id << " ready." << std::endl;
}

/** Unload image files from GPU memory */
void Node::unready(){
	if(!_ready) return;
	glDeleteTextures(6,imagemap.glNames);
	
	_ready = false;
}

/** Return true if this node is ready, false otherwise. */
bool Node::isReady(){
	return _ready;
}

/** Return a pointer to the imagemap structure. */
cubemap_t *Node::getImagemap(){
	return &imagemap;
}

/** Get the node's id. */
const std::string Node::getId(){
	return id;
}

/** Returns the hotspot under a given angle.  They are considered in the order
 * in which they are defined. */
hotspot_t *Node::getHotSpot(GLdouble xangle,GLdouble yangle){
	for(unsigned int i = 0; i < hotspots.size(); i++){
		//printf("hotspot: %f, %f\n", sqr(hotspots[i].alt - yangle) + sqr(hotspots[i].az - xangle), sqr(hotspots[i].size));
		if(sqr(hotspots[i].alt - yangle) + sqr(hotspots[i].az - xangle) < 
				sqr(hotspots[i].size)){
			//printf("active hotspot %d\n", i);
			return &hotspots[i];
		}
	}
	return NULL;
}

