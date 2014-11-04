a simple drop-in to add text rendering to a shader-based OpenGL project

you will need text.h and text.cpp to your project, as well as stb_image.h

example of usage in example.cpp

i assume that you are using GLEW + GLFW3 to start opengl, but you can change
this in text.h

i also assume that you are using OpenGL 4.0 with GLSL 4.0.0. you can change
this around pretty easily - the shaders are hard-coded in text.cpp

the FreeMono font files work, and if you want to use a different font you can
grab the generator tool i made from:

https://github.com/capnramses/antons_opengl_tutorials_book/tree/master/27_font_atlas

