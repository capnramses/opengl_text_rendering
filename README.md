a simple drop-in to add text rendering to a shader-based OpenGL project

#Example#

See example.cpp for a minimal OpenGL 4 example that uses text rendering

#Assumptions#

* you are using GLEW + GLFW3 to start opengl - you can easily change the #includes in text.h
* You are using OpenGL 4 and GLSL 4.0.0 - make minor changes to shaders in text.cpp to adjust
* You are happy using one font for all your text - your could easily upgrade this
* You are using a C++ compiler - this could should compile with a C compiler too (#include <stdbool.h>)

#Setup#

You don't need to pre-compile anything - just add these files to your project:
* text.h
* text.cpp
* stb_image.h (this image loader is from https://github.com/nothings/stb)

Put these files in your run-time directory:
* freemono.png
* freemono.meta

#Usage#

* In your main.cpp #include "text.h"
* before your rendering loop:
`
init_text_rendering ("freemono.png", "freemono.meta", viewport_width, viewport_height);
int hello_id = add_text ("Hello world!", -0.75, 0.5, 100.0f, 0.5f, 0.5f, 1.0f, 1.0f);
`

* during your rendering loop:
`draw_texts ();`

#Adding Other Fonts#

You can grab the generator tool that i made from:

https://github.com/capnramses/antons_opengl_tutorials_book/tree/master/27_font_atlas

