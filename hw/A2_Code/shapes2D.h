#ifndef __ALEX_SHAPES2D_H__
#define __ALEX_SHAPES2D_H__

#include "Angel.h"
#include "Shape.h"

class Point2D: public Shape{
	public:
		Point2D(vec3 p0): Shape(1)
		{ vec3 points[1] = {p0};
		  this->set_points(points); this->set_color(vec4(1.0, 0, 0, 1.0));}

		Point2D(): Shape(1)
		{ vec3 points[1]; points[0] = vec3(-0.2,0,1);
		  this->set_points(points); 
		  this->set_color(vec4(0.0, 0, 1.0, 1.0)); } 
};

class Line2D: public Shape {
	public:
		Line2D(vec3* points): Shape(2)
		{ this->set_points(points);
	  	  this->set_color(vec4(1.0, 0, 0, 1.0)); }

		Line2D(vec3 p0, vec3 p1): Shape(2)
		{ vec3 points[2] = {p0, p1};
		  this->set_points(points);this->set_color(vec4(1.0, 0, 0, 1.0));}

		Line2D(): Shape(2)
		{ vec3 points[2]; points[0] = vec3(-0.2,0,1);
		  points[1] = vec3(0.2,0,1); this->set_points(points); 
		  this->set_color(vec4(0.0, 0, 1.0, 1.0));} 
		
		float get_slope()
		{ return (get_points()[0].x - get_points()[1].x) / \
				 (get_points()[0].y - get_points()[1].y); }

		vec3 intersection(Line2D other);
};

class Triangle2D: public Shape {
	public:
		Triangle2D(vec3* points): Shape(3)
		{ this->set_points(points);
	  	  this->set_color(vec4(1.0, 0, 0, 1.0)); }

		Triangle2D(vec3 p0, vec3 p1, vec3 p2): Shape(3)
		{ vec3 points[3] = {p0, p1, p2};
		  this->set_points(points);this->set_color(vec4(1.0, 0, 0, 1.0));}
			
		Triangle2D(): Shape(3)
		{ vec3 points[3]; points[0] = vec3(-0.2,0,1);
		  points[1] = vec3(0.2,0,1); points[2] = vec3(0, 1, 1);
		  this->set_points(points); this->set_color(vec4(0.0, 0, 1.0, 1.0));} 

		vec3 get_center();

		

	private:	
		void build_shape(){}
	};

class Rectangle: public Shape {
	Triangle2D _triangles[2];
	public:
		Rectangle(vec3* p): Shape()
		{ this->set_color(vec4(1.0, 0, 0, 1.0));
		  _triangles[0] = Triangle2D(p[0], p[1], p[2]);
		  _triangles[1]= Triangle2D(p[2], p[3], p[0]);}

	/*	
		Rectangle(vec3 p0, vec3 p1, vec3 p2, vec3 p3): Shape()
		{ vec3 points[4] = {p0, p1, p2, p3};
		  this->set_points(points); this->set_color(vec4(1.0, 0, 0, 1.0));}*/

/*		Rectangle(): Shape()
		{ vec3 points[4]; points[0] = vec3(-0.2,0,1);
		  points[1] = vec3(0.2,0,1); points[2] = vec3(0.2,0.2,1); 
		  points[3] = vec3(-0.2, 0.2, 1);
		  this->set_points(points); this->set_color(vec4(1.0, 0, 0,1.0));} 
*/
		vec3 get_center();

		static Rectangle build_sqaure(vec3 center, float radius);

		void build();

		void draw();

		void setModelMatrix(mat3 mm)
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


class Circle: public Shape {
	unsigned short int _precision ; // num of triangles
	Triangle2D *_triangles ;
	vec3 _pos ;
	float _radius ;
	public:
		Circle (vec3 pos, float radius, 
			   unsigned short int precision=100): Shape()
		{ _triangles = new Triangle2D[precision]; _radius = radius; _pos = pos; _precision = precision; }

		Circle(): Shape()
		{ _triangles = new Triangle2D[100]; _radius = .3; _pos = vec3(0.0, 0.0); _precision = 100; }

		void set_triangle_color(int index, vec4 color)
		{ _triangles[index].set_color(color); }

		unsigned short int get_precision()
		{ return _precision; }

		void set_precision(unsigned short int precision)
		{ _precision = precision; }

		vec3 get_pos()
		{ return _pos; }

		void set_pos(vec3 pos)
		{ _pos = pos; }

		float get_radius()
		{ return _radius; }

		void set_radius(float radius)
		{ _radius = radius; }

		vec3* get_points();

		void draw();

		void build();

		 Triangle2D* get_triangles()
		{ return _triangles; }

		vec3 get_center()
		{ return this->_pos; }

	private:
		void build_shape();
};

#endif 
