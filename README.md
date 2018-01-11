a simple drop-in to add text rendering to a shader-based OpenGL project

# Example

See example.cpp for a minimal shader-based OpenGL 2.1 example that uses text rendering

# Assumptions

* you are using GLEW + GLFW3 to start opengl - you can easily change the #includes in text.h
* You are using OpenGL 2.1 or newer and GLSL 1.2.0 or newer - make minor changes to shaders in text.cpp to adjust
* You are happy using one font for all your text - you could easily upgrade this
* You are using a C++ compiler - this should compile with a C compiler too - ```#include <stdbool.h>```

# Setup

You don't need to pre-compile anything - just add these files to your project:
* text.h
* text.cpp
* stb_image.h (this image loader is from https://github.com/nothings/stb)

If you are already using stb_image then remove the #define at the top of text.cpp

Put these files in your run-time directory:
* freemono.png
* freemono.meta

# Usage

* In your main.cpp ```#include "text.h"```
* before your rendering loop:
```
init_text_rendering ("freemono.png", "freemono.meta", viewport_width, viewport_height);
// x and y are -1 to 1
// size_px is the maximum glyph size in pixels (try 100.0f)
// r,g,b,a are red,blue,green,opacity values between 0.0 and 1.0
// if you want to change the text later you will use the returned integer as a parameter
int hello_id = add_text ("Hello world!", x, y, size_px, r, g, b, a);
```
* during your rendering loop:
```
draw_texts ();
```
# Adding Other Fonts

The fonts have a .meta file which gives the size and offset of each glyph.
You could draw your own atlas by hand and manually tweak its .meta file.
I also made a generator that takes a TTF font and makes a .png and a .meta from it:
https://github.com/capnramses/antons_opengl_tutorials_book/tree/master/27_font_atlas

