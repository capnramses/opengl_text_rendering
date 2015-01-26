//
// Example GL programme to test text rendering
// Anton Gerdelan, 4 Nov 2014
// Assumes using GLEW and GLFW3 libraries

#include "text.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// files to use for font. change path here
const char* atlas_image = "freemono.png";
const char* atlas_meta = "freemono.meta";

int gl_width = 600;
int gl_height = 600;
GLFWwindow* gl_window;

int main () {
	// for drawing a triangle
	GLuint vao;
	GLuint shader_programme;

	//
	// initialise GL
	assert (glfwInit ());
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
//	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	gl_window = glfwCreateWindow (
		gl_width, gl_height, "Text Example", NULL, NULL);
	assert (gl_window);
	glfwMakeContextCurrent (gl_window);
	glewExperimental = GL_TRUE;
	glewInit ();
	const GLubyte* renderer = glGetString (GL_RENDERER);
	const GLubyte* version = glGetString (GL_VERSION);
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version: %s\n", version);
	glDepthFunc (GL_LESS);
	glEnable (GL_DEPTH_TEST);
	glCullFace (GL_BACK);
	glFrontFace (GL_CCW);
	glEnable (GL_CULL_FACE);
	glClearColor (0.2, 0.2, 0.2, 1.0);
	glViewport (0, 0, gl_width, gl_height);
	
	//
	// add some geometry
	{
		float points[] = {
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.0f,  0.5f,  0.0f
		};
		GLuint vbo = 0;
		
		glGenBuffers (1, &vbo);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);
		glGenVertexArrays (1, &vao);
		glBindVertexArray (vao);
		glEnableVertexAttribArray (0);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	
	//
	// shader for the geometry
	{
		const char* vertex_shader =
		"#version 120\n"
		"attribute vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}";
		const char* fragment_shader =
		"#version 120\n"
		"void main () {"
		"  gl_FragColor = vec4 (0.2, 0.2, 0.6, 1.0);"
		"}";
		GLuint vs = glCreateShader (GL_VERTEX_SHADER);
		glShaderSource (vs, 1, &vertex_shader, NULL);
		glCompileShader (vs);
		GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
		glShaderSource (fs, 1, &fragment_shader, NULL);
		glCompileShader (fs);
		shader_programme = glCreateProgram ();
		glAttachShader (shader_programme, fs);
		glAttachShader (shader_programme, vs);
		glLinkProgram (shader_programme);
	}

	//
	// initialise font, load from files
	assert (init_text_rendering (atlas_image, atlas_meta, gl_width, gl_height));
	printf ("adding text...\n");
	int hello_id = add_text (
		"Hello\nis it me you're looking for?",
		-0.9f, 0.5f, 35.0f, 0.5f, 0.5f, 1.0f, 1.0f);
	
	int time_id = add_text (
		"The time is:",
		-1.0f, 1.0f, 40.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	move_text (time_id, -1.0f, 1.0f);
	
	//
	// display stuff
	while (!glfwWindowShouldClose (gl_window)) {
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// draw geometry
		glUseProgram (shader_programme);
		glBindVertexArray (vao);
		glDrawArrays (GL_TRIANGLES, 0, 3);
		
		// update the text for the timer
		double t = glfwGetTime ();
		char tmp[256];
		sprintf (tmp, "The time is: %f\n", t);
		update_text (time_id, tmp);
		float r = fabs (sinf (t));
		float g = fabs (sinf (t + 1.57f));
		change_text_colour (time_id, r, g, 0.0f, 1.0f);
		
		// draw all the texts
		draw_texts ();
		
		glfwPollEvents ();
		glfwSwapBuffers (gl_window);
	}
	
	//
	// clean-up window etc.
	glfwTerminate();
	return 0;
}
