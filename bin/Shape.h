#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Angel.h"
#include "Drawable.h"
#include <algorithm>

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

private:
	vec4* vertexLocations;
	int n; // # of points
	vec4* colors;
	GLenum draw_mode;
	bool compound;

protected:
	virtual void build_shape()
	{}
			
};

#endif
