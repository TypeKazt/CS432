#ifndef __ALEX_SHAPES_H__
#define __ALEX_SHAPES_H__

#include "Angel.h"
#include "Shape.h"

class Point: public Shape{
	public:
		Point(vec4 p0): Shape(1)
		{ vec4 points[1] = {p0};
		  this->set_points(points); this->set_color(vec4(1.0, 0, 0, 1.0));}

		Point(): Shape(1)
		{ vec4 points[1]; points[0] = vec4();
		  this->set_points(points); 
		  this->set_color(vec4(0.0, 0, 1.0, 1.0)); } 
};

class Line: public Shape {
	public:
		Line(vec4* points): Shape(2)
		{ this->set_points(points);
	  	  this->set_color(vec4(1.0, 0, 0, 1.0)); }

		Line(vec4 p0, vec4 p1): Shape(2)
		{ vec4 points[2] = {p0, p1};
		  this->set_points(points);this->set_color(vec4(1.0, 0, 0, 1.0));}

		Line(): Shape(2)
		{ vec4 points[2]; points[0] = vec4(-0.2,0,1);
		  points[1] = vec4(0.2,0,1); this->set_points(points); 
		  this->set_color(vec4(0.0, 0, 1.0, 1.0));} 
		
		float get_slope()
		{ return (get_points()[0].x - get_points()[1].x) / \
				 (get_points()[0].y - get_points()[1].y); }

		vec4 intersection(Line other);
};

class Triangle: public Shape {
	public:
		Triangle(vec4* points): Shape(3)
		{ this->set_points(points);
	  	  this->set_color(vec4(1.0, 0, 0, 1.0)); }

		Triangle(vec4 p0, vec4 p1, vec4 p2): Shape(3)
		{ vec4 points[3] = {p0, p1, p2};
		  this->set_points(points);this->set_color(vec4(1.0, 0, 0, 1.0));}
			
		Triangle(): Shape(3)
		{ vec4 points[3]; points[0] = vec4(-0.2,0,0,1);
		  points[1] = vec4(0.2,0,0,1); points[2] = vec4(0, 1, 0,1);
		  this->set_points(points); this->set_color(vec4(0.0, 0, 1.0, 1.0));} 

		vec4 get_center();

		

	private:	
		void build_shape(){}
	};

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
