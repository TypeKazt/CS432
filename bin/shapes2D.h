#ifndef __ALEX_SHAPES2D_H__
#define __ALEX_SHAPES2D_H__

#include "Angel.h"

//vec4 black = vec4(1.0, 1.0, 1.0, 1.0);

class Triangle2D {
	vec2 **_points ;
	vec4 _color ;
	public:
		Triangle2D(vec2* p0, vec2* p1, vec2* p2/*, vec4 color=black*/)
		{ _points = new vec2*[3]; _points[0] = p0; _points[1] = p1; 
		  _points[2] = p2; _color = vec4(1.0, 1.0, 1.0, 1.0); }

		Triangle2D(){}

		void set_color(vec4 color)
		{ _color = color; }

		vec4 get_color()
		{ return _color; }

		vec2** get_points()
		{ return _points; }
};


class Circle {
	unsigned short int _precision ; // num of triangles
	Triangle2D **_triangles ;
	vec2* _pos ;
	float _radius ;
	public:
		Circle (vec2* pos, float radius, 
			   unsigned short int precision=100)
		{ _triangles = new Triangle2D*[precision]; _radius = radius; _pos = pos; _precision = precision; }
		
		void set_triangle_color(int index, vec4 color)
		{ _triangles[index]->set_color(color); }

		void generate_circle();

		vec2** get_points();

		unsigned short int get_precision()
		{ return _precision; }

		void set_precision(unsigned short int precision)
		{ _precision = precision; }

		vec2* get_pos()
		{ return _pos; }

		void set_pos(vec2* pos)
		{ _pos = pos; }

		float get_radius()
		{ return _radius; }

		void set_radius(float radius)
		{ _radius = radius; }

};

#endif 
