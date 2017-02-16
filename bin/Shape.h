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

	virtual void set_color(vec4 color)
	{ this->color = color; }
	
	virtual vec4 get_color()
	{ return this->color; }

	virtual vec4* get_points()
	{ return vertexLocations; }

	virtual void set_points(vec4*);

	virtual void draw();

	int get_n()
	{ return n; }

	void set_draw_mode(GLenum dm)
	{ draw_mode = dm; }

	virtual vec4 get_center()
	{return vec4(0, 0, 0, 0);}

private:
	vec4* vertexLocations;
	int n; // # of points
	vec4 color;
	GLenum draw_mode;

protected:
	virtual void build_shape();
			
};
#endif
