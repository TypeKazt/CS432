#include "Angel.h"
#include "Rectangle.h"

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


