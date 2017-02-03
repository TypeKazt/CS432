#include "shapes2D.h"
#include "Angel.h"
#include <math.h>
#include "vec.h"

vec3 Line2D::intersection(Line2D other)
{
	const vec3 r = vec3(1, get_slope(), 1);
	const vec3 s = vec3(1, other.get_slope(), 1);
	const vec3 p = get_points()[0];
	const vec3 q = other.get_points()[0];
//	vec3 t = cross(q-p, s)/cross(r, s);
	return p;
}

vec3 Triangle2D::get_center()
{
	vec3* p = get_points();
	return vec3((p[0].x + p[1].x + p[2].x)/3, (p[0].y + p[1].y + p[2].y)/3, 1);
	/*
	vec3 d0 = ((p[1] - p[0]) + (p[2] - p[0])) / 2;
	vec3 d1 = ((p[2] - p[1]) + (p[0] - p[1])) / 2;
	Line2D l0 = Line2D(p[0], p[0] + d0);
	Line2D l1 = Line2D(p[1], p[1] + d1);
	return l0.intersection(l1);*/
}

vec3 Rectangle:: get_center()
{
	vec3 p0 = _triangles[0].get_points()[0];
	vec3 p2 = _triangles[0].get_points()[2];
	vec3 delta = p2 - p0;
	return p0 + delta/2.0;
}

Rectangle Rectangle::build_sqaure(vec3 center, float radius)
{
	float fvdeg = 45.0/360.0 * 2.0 * M_PI; 
	vec3 p[4];
	p[0] = center + vec3(cos(fvdeg)*radius, sin(fvdeg)*radius, 1);
	p[1] = center + vec3(cos(3.0*fvdeg)*radius, sin(3.0*fvdeg)*radius, 0);
	p[2] = center + vec3(cos(5.0*fvdeg)*radius, sin(5.0*fvdeg)*radius, 0);
	p[3] = center + vec3(cos(7.0*fvdeg)*radius, sin(7.0*fvdeg)*radius, 0);
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
	vec3 center = this->get_pos();
	vec3* prev_point = new vec3(center.x + this->get_radius(), 
								center.y, 0) ;
	float incr = 2*M_PI / float(this->get_precision()) ;

	float count = 0.0 ;
	for (int i = 1; i <= this->get_precision(); i++)
	{
		count += incr ;
		vec3* new_point = new vec3(center.x + this->get_radius() * cos(count),
					   			   center.y + this->get_radius() * sin(count), 0) ;	
		Triangle2D myt = *(new Triangle2D(this->get_pos(), *prev_point, *new_point));
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

vec3* Circle::get_points()
{
	vec3* my_points = new vec3[3 * this->get_precision()] ;
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
