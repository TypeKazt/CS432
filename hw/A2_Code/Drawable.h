#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__
#include "Angel.h"
#include <vector>

using namespace std;

class Drawable {
protected:
	GLuint program;
	GLuint VAO;
	GLuint VBO;
	mat3 modelmatrix;
	
public:
	virtual void draw()=0;
	virtual void setModelMatrix(mat3 mm) { modelmatrix = mm; }
	void set_shader(GLuint sp)
	{ program = sp; }
	mat3 get_model_matrix()
	{ return modelmatrix; }
	virtual vec3 get_center()=0;
	virtual vec4 get_color()=0;
	virtual void set_color(vec4)=0;
};

#endif
