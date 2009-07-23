/** @file terras.h
 * Data structures and prototypes used throughout the Terras engine.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#ifndef __TERRAS_H__
#define __TERRAS_H__

// Common libraries assumed to be present in other files
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>

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

class Node;
class CubeNode;

class Callback;
class PythonCallback;

extern Model *model;
extern Node *currNode;

#endif
