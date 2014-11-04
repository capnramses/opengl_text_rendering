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

#include "text.h"
#include "stb_image.h" // Sean Barrett's image loader
#include <stdio.h>

// size of atlas. my handmade image is 16x16 glyphs
#define ATLAS_COLS 16
#define ATLAS_ROWS 16

GLuint font_texture;
float glyph_y_offsets[256] = { 0.0f };
float glyph_widths[256] = { 0.0f };

bool load_font_meta (const char* meta_file) {
	char line [128];
	int ascii_code = -1;
	float prop_xMin = 0.0f;
	float prop_width = 0.0f;
	float prop_yMin = 0.0f;
	float prop_height = 0.0f;
	float prop_y_offset = 0.0f;
	FILE* fp = NULL;
	
	fp = fopen (meta_file, "r");
	if (!fp) {
		fprintf (stderr, "ERROR: could not open file %s\n", meta_file);
		return false;
	}
	// get header line first
	fgets (line, 128, fp);
	// loop through and get each glyph's info
	while (EOF != fscanf (
		fp, "%i %f %f %f %f %f\n",
		&ascii_code,
		&prop_xMin,
		&prop_width,
		&prop_yMin,
		&prop_height,
		&prop_y_offset
	)) {
		glyph_widths[ascii_code] = prop_width;
		glyph_y_offsets[ascii_code] = 1.0 - prop_height - prop_y_offset;
	}
	fclose (fp);
	return true;
}

bool load_font_texture (const char* file_name, GLuint* tex) {
	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = NULL;
	int width_in_bytes = -1;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = -1;
	
	image_data = stbi_load (file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf (stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf (
			stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name
		);
	}
	width_in_bytes = x * 4;
	half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
	glGenTextures (1, tex);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, *tex);
	glTexImage2D (
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		x,
		y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image_data
	);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return true;
}

//
// load files for rendering;
// 1. an atlas image containing the pixels of all glyphs (characters)
// expected format is 16x16 glyphs (256 total)
// 2. a text file, describing size and offset of each character in the image
// returns false if could not load files
bool load_font (const char* atlas_image, const char* atlas_meta) {
	if (!load_font_texture (atlas_image, &font_texture)) {
		return false;
	}
	if (!load_font_meta (atlas_meta)) {
		return false;
	}
	return true;
}
