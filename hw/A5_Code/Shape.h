#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Angel.h"
#include "Drawable.h"
#include <algorithm>
#include "Surface.h"

class Shape: public Drawable{  //derived from drawable class


public:	

	//constructors
	Shape(int);
	Shape();
	
	//destructor
	~Shape();

	virtual void build();

	void set_color(vec4);

	void set_vertex_color(int index, vec4 color)
	{ colors[index] = color; }
	
	vec4* get_colors()
	{ return this->colors; }

	vec4* get_points()
	{ return vertexLocations; }

	vec4* get_normals()
	{ return normals; }

	void set_normal(int index, vec4 n)
	{ normals[index] = n; }

	void set_point(int index, vec4 p)
	{ vertexLocations[index] = p; }

	virtual void set_points(vec4*);

	void draw();

	int get_n()
	{ return n; }

	void set_n(int);

	void set_draw_mode(GLenum dm)
	{ draw_mode = dm; }

	virtual vec4 get_center()
	{return vec4(0, 0, 0, 0);}

	void set_surface(vec4 a, vec4 d, vec4 s, float sh)
	{ surf = Surface(a, d, s, sh); }

private:
	vec4* vertexLocations;
	int n; // # of points
	vec4* colors;
	vec4* normals;
	GLenum draw_mode;
	bool compound;
	Surface surf;

	GLuint vPosition, vNormal, model_loc;
	GLuint diffuse_loc, spec_loc, ambient_loc, alpha_loc;

protected:
	virtual void build_shape()
	{}
			
};

#endif
