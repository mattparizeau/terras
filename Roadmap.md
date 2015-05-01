# Required Features #
  * Solid OpenGL cube rendering that should not show gaps in the cube under any circumstances. _Partial_
  * YAML support for configuration files and node definitions. _Partial_
  * Traversal of the graph from within the game.
  * Scripting or other interactivity support to actually create puzzles
  * Sound and music support through SDL\_mixer.

# Secondary Features #
  * A small but legitimate test game.  Rendering should probably be done in either [POV-Ray](http://www.povray.org/) or [Blender](http://www.blender.org).
  * Animation support (full-screen or only part of the frame).
  * Advanced audio support (3D stereo, 5.1 support?).

# Longer-term Feature Proposals #
  * HDR support with the ability to vary exposure with some sensitivity to light.  Perhaps the effect could even be applied slowly, similar to how we react to a dark room or bright light.
  * GLSL depth support, rendering either realtime fog or adding focal blur depending on the depth under the cursor.  Other features to add depth to prerendered scenes should be considered.
