#ifndef __ALEX_SHAPES2D_H__
#define __ALEX_SHAPES2D_H__

#include "Angel.h"
#include "Shape.h"

//vec4 black = vec4(1.0, 1.0, 1.0, 1.0);

class Triangle2D: public Shape {
		public:
			Triangle2D(vec3* points): Shape(3)
			{ this->set_points(points); }

			Triangle2D(vec3 p0, vec3 p1, vec3 p2): Shape(3)
			{ vec3 points[3] = {p0, p1, p2};
		  	  this->set_points(points);this->set_color(vec4(1.0, 0, 0,1.0));}
			
			Triangle2D(): Shape(3)
			{ vec3 points[3]; points[0] = vec3(-0.2,0,1);
			  points[1] = vec3(0.2,0,1); points[2] = vec3(0,1,1);
			  this->set_points(points); this->set_color(vec4(1.0, 0, 0,1.0));} 

		private:	
			void build_shape(){}
		
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

	private:
		void build_shape();
};

#endif 
