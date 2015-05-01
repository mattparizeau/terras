# Framework Design #

I've become a little concerned that the MVC model is not being adhered to particularly well.  I'm interested in re-engineering almost everything to get a more elegant and easy-to-work with solution, so that hopefully I can encapsulate the functions that work with other libraries into single classes.

# Class Outlines #
Some thought should be given to the order in which classes should be instantiated.  Specifically, we would like to use the model for configuration information regarding the view.  The constructor for the model should take a YAML configuration file path as an argument, which will read video configuration.  The controller should follow, and the view should be instantiated last, as it does not set any sort of state, but only reads it.

## View ##
The view should interface with SDL exclusively.  The current design throws SDL code around all over several classes.  We need 2D and 3D drawing capability, and perhaps the cursor should be built into the view functionality.

## Controller ##
The controller should handle all callbacks.  Game logic will be implemented in Python for ease of programming (and keeping it completely seperate from the framework implementation.  Callbacks to Python and node state changes should be possible from within Python.

## Model ##
Read in YAML configuration files and node description files.  These will include the names of the callbacks to Python from the controller.

## Node ##
This class links the Model, View, and Controller classes and implements state (which, in the context of node-based adventure games is usually position).  Clicks should be handled differently in different nodes.  Music may change (although nothing has been done in that direction yet).

# Configuration #
Configuration files should be exlcusively in YAML, which is simultaneously easy to read by machine (we are using libyaml-cpp) and write by hand.

## Node Configuration ##
A node configuration file will look something like this:
```
%YAML 1.1
---
id: "node1"
imagemaps: 
	- "test/test0.bmp"
	- "test/test1.bmp"
	- "test/test2.bmp"
	- "test/test3.bmp"
	- "test/test4.bmp"
	- "test/test5.bmp"
hotspots:
	- {alt: 23, az: 40, size: 15, call: "MyPythonFunction"} 
```