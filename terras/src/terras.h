/** @file terras.h
 * Data structures and prototypes used throughout the Terras engine.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#ifndef __TERRAS_H__
#define __TERRAS_H__

// Common libraries assumed to be present in other files
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
//#include <boost/scoped_ptr.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/weak_ptr.hpp>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <map>

#include "yaml.h"

#define DEBUG 
// #ifndef DEBUG
// #define DEBUG 0
// #endif
/* Class predefinitions */
class Model;
class View;

class Node;
class CubeNode;

class Callback;
class PythonCallback;

extern Model *model;
extern Node *currNode;

#endif
