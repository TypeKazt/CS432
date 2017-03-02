#ifndef __ALEX_CIRCLE_H__
#define __ALEX_CIRCLE_H__

#include "Angel.h"
#include "Shape.h"
#include "Triangle.h"


class Circle: public Shape {
	unsigned short int _precision ; // num of triangles
	Triangle *_triangles ;
	vec4 _pos ;
	float _radius ;
	public:
		Circle (vec4 pos, float radius, 
			   unsigned short int precision=100): Shape()
		{ _triangles = new Triangle[precision]; _radius = radius; _pos = pos; _precision = precision; }

		Circle(): Shape()
		{ _triangles = new Triangle[100]; _radius = .3; _pos = vec4(0.0, 0.0); _precision = 100; }

		void set_triangle_color(int index, vec4 color)
		{ _triangles[index].set_color(color); }

		unsigned short int get_precision()
		{ return _precision; }

		void set_precision(unsigned short int precision)
		{ _precision = precision; }

		vec4 get_pos()
		{ return _pos; }

		void set_pos(vec4 pos)
		{ _pos = pos; }

		float get_radius()
		{ return _radius; }

		void set_radius(float radius)
		{ _radius = radius; }

		vec4* get_points();

		void draw();

		void build();

		 Triangle* get_triangles()
		{ return _triangles; }

		vec4 get_center()
		{ return this->_pos; }

	private:
		void build_shape();
};

#endif
