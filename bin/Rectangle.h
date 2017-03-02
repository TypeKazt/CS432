#ifndef __ALEX_RECTANGLE_H__
#define __ALEX_RECTANGLE_H__

#include "Angel.h"
#include "Shape.h"
#include "Triangle.h"


class Rectangle: public Shape {
	Triangle _triangles[2];
	public:
		Rectangle(vec4* p): Shape()
		{ this->set_color(vec4(1.0, 0, 0, 1.0));
		  _triangles[0] = Triangle(p[0], p[1], p[2]);
		  _triangles[1]= Triangle(p[2], p[3], p[0]);}


		Rectangle(vec4 p0, vec4 p1, vec4 p2, vec4 p3): Shape()
		{ vec4 points[4] = {p0, p1, p2, p3};
		  this->set_points(points); this->set_color(vec4(1.0, 0, 0, 1.0));}

		Rectangle(): Shape()
		{ vec4 points[4]; points[0] = vec4(-0.2,0,0,1);
		  points[1] = vec4(0.2,0,0,1); points[2] = vec4(0.2,0.2,0,1); 
		  points[3] = vec4(-0.2, 0.2, 0, 1);
		  this->set_points(points); this->set_color(vec4(1.0, 0, 0,1.0));} 

		vec4 get_center();

		static Rectangle build_sqaure(vec4 center, float radius);

		void build();

		void draw();

		void setModelMatrix(mat4 mm)
		{ _triangles[0].setModelMatrix(mm);
		  _triangles[1].setModelMatrix(mm);
		  modelmatrix = mm;}

	void set_color(vec4 color)
		{
			_triangles[0].set_color(color);
			_triangles[1].set_color(color);
		}

	vec4 get_color()
	{ return _triangles[0].get_color(); }

	private:
		void build_shape();
};

#endif
