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
	void setModelMatrix(mat3 mm) { modelmatrix = mm; }
	void set_shader(GLuint sp)
	{ program = sp; }
};

#endif
