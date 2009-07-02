

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
class TerraController;
class TerraModel;
class TerraView;
class TerraNode;
class TerraCursor;


