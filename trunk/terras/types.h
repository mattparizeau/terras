

/** Stores hotspots and associated callbacks. */
struct hotspot_t{
// Example: {alt: 23, az: 40, size: 15, call: "MyPythonFunction"} 
	std::string callback;
	GLdouble alt, az, size;
};

/** Orientation for the faces of a cube:
 * North, South, East, West, Up, Down.  Deprecated.
 */
enum orient_t {N=0,E,S,W,U,D};

/** Cursor mode.
 */
enum cursor_mode_t {
	CURSOR_POINTER,
	CURSOR_LOCKED
};
#define NUM_CURSORS 2

/* Class definitions for later */
class Controller;
class Model;
class View;
class Node;
class Cursor;


