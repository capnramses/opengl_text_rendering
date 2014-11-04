//
// Simple OpenGL Text Rendering Functions
// Dr Anton Gerdelan, Trinity College Dublin, Ireland
// First version 4 Nov 2014
// =Pros=
// * will just magically work
// * easy-ish to change the font
// =Cons=
// * i didn't add support to render multiple fonts at once (but trivial to add)
// =Dependencies=
// Sean Barrett's public domain image loader lib: stb_image.h (included)
//

#ifndef _TEXT_H_
#define _TEXT_H_

// change or comment these out if using different OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//
// load files for rendering;
// 1. an atlas image containing the pixels of all glyphs (characters)
// expected format is 16x16 glyphs (256 total)
// 2. a text file, describing size and offset of each character in the image
// returns false if could not load files
bool load_font (const char* atlas_image, const char* atlas_meta);

#endif
