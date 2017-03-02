#ifndef __ALEX_POLYHEDRON_H__
#define __ALEX_POLYHEDRON_H__

#include "Angel.h"
#include "Shape.h"
#include "Triangle.h"


class Polyhedron: public Shape {
	Triangle *_triangles ;
	unsigned int size;
	public:
		Polyhedron(Triangle *t, unsigned int size): Shape()
		{ _triangles = t; this->size = size;}
		
		Polyhedron(): Shape()
		{size = 0;}	

		void set_triangles(Triangle* t, unsigned int size)
		{ _triangles = t; this->size = size; }

		void set_triangle_color(unsigned int index, vec4 color)
		{ _triangles[index].set_color(color); }

		unsigned int get_size()
		{ return size; }

		Triangle* get_triangles()
		{ return _triangles; }

		void build();

		void draw(); 

		void setModelMatrix(mat4);

	private:
		void build_shape();
};

#endif 
