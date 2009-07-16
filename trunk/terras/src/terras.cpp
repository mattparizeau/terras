/** @file terras.cpp
 * Main function and other important initialization functions.
 * @author Peter Hokanson [pchokanson@gmail.com]
 */

#include <stdio.h>

#include "terras.h"
#include "model.h"

/** Entry point for terras. */
int main(int argc, char **argv){
	Model *model = new Model(argv[0], "data/terraslogic.py");
	return 0;
}

