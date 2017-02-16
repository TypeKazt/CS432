#include "shapes.h"
#include "Angel.h"
#include <math.h>
#include "vec.h"

vec4 Line::intersection(Line other)
{
	const vec4 r = vec4(1, get_slope(), 1);
	const vec4 s = vec4(1, other.get_slope(), 1);
	const vec4 p = get_points()[0];
	const vec4 q = other.get_points()[0];
//	vec4 t = cross(q-p, s)/cross(r, s);
	return p;
}

vec4 Triangle::get_center()
{
	vec4* p = get_points();
	return vec4((p[0].x + p[1].x + p[2].x)/3, 
				(p[0].y + p[1].y + p[2].y)/3, 
				(p[0].z + p[1].z + p[2].z)/3, 1);
}

vec4 Rectangle:: get_center()
{
	vec4 p0 = _triangles[0].get_points()[0];
	vec4 p2 = _triangles[0].get_points()[2];
	vec4 delta = p2 - p0;
	return p0 + delta/2.0;
}

Rectangle Rectangle::build_sqaure(vec4 center, float radius)
{
	float fvdeg = 45.0/360.0 * 2.0 * M_PI; 
	vec4 p[4];
	p[0] = center + vec4(cos(fvdeg)*radius, sin(fvdeg)*radius, 0, 1);
	p[1] = center + vec4(cos(3.0*fvdeg)*radius, sin(3.0*fvdeg)*radius, 0, 0);
	p[2] = center + vec4(cos(5.0*fvdeg)*radius, sin(5.0*fvdeg)*radius, 0, 0);
	p[3] = center + vec4(cos(7.0*fvdeg)*radius, sin(7.0*fvdeg)*radius, 0, 0);
	Rectangle result = Rectangle(p);
	return result;	
}

void Rectangle::build_shape()
{
	_triangles[0].set_color(get_color());
	_triangles[1].set_color(get_color());
	_triangles[0].set_shader(program);
	_triangles[1].set_shader(program);

}

void Rectangle::build()
{
	build_shape();
	_triangles[0].build();
	_triangles[1].build();
}

void Rectangle::draw()
{
	_triangles[0].draw();
	_triangles[1].draw();
}

void Circle::build_shape()
{
	vec4 center = this->get_pos();
	vec4* prev_point = new vec4(center.x + this->get_radius(), 
								center.y, 0, 1) ;
	float incr = 2*M_PI / float(this->get_precision()) ;

	float count = 0.0 ;
	for (int i = 1; i <= this->get_precision(); i++)
	{
		count += incr ;
		vec4* new_point = new vec4(center.x + this->get_radius() * cos(count),
					   			   center.y + this->get_radius() * sin(count), 0, 1) ;	
		Triangle myt = *(new Triangle(this->get_pos(), *prev_point, *new_point));
		myt.set_color(_triangles[i-1].get_color());
		this->_triangles[i-1] = myt;
		this->_triangles[i-1].set_shader(program);
		prev_point = new_point;
	}
}

void Circle::build()
{
	build_shape();
	for (int i = 0; i < this->_precision; i++)
		this->_triangles[i].build();	
}

vec4* Circle::get_points()
{
	vec4* my_points = new vec4[3 * this->get_precision()] ;
	int count = 0 ;
	for(int i = 0; i < this->get_precision() ; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			my_points[count] = this->_triangles[i].get_points()[j] ;
			count += 1 ;
		}
	}

	return my_points ;

}

void Circle::draw()
{
	for (int i = 0; i < this->_precision; i++)
		this->_triangles[i].draw();
}

void Polyhedron::build()
{
	for (unsigned int i = 0; i < this->size; i++)
		this->_triangles[i].build();
}

void Polyhedron::draw()
{
	for (unsigned int i = 0; i < this->size; i++)
		this->_triangles[i].draw();
}

void Polyhedron::setModelMatrix(mat4 mm)
{
	for (unsigned int i = 0; i < this->size; i++)
		this->_triangles[i].setModelMatrix(mm);
}

void Polyhedron::build_shape()
{
	for(int i = 0; i < size; i++)
		_triangles[i].set_shader(program);
}
