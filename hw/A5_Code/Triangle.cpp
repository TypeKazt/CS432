#include "Angel.h"
#include "vec.h"
#include "Triangle.h"


Triangle::Triangle(vec4* points): Shape(3)
{ this->set_points(points);
  this->set_color(vec4(1.0, 0, 0, 1.0)); }

Triangle::Triangle(vec4 p0, vec4 p1, vec4 p2): Shape(3)
{ vec4 points[3] = {p0, p1, p2};
  this->set_points(points);this->set_color(vec4(1.0, 0, 0, 1.0));}

Triangle::Triangle(): Shape(3)
{ vec4 points[3]; points[0] = vec4(-0.2,0,0,1);
  points[1] = vec4(0.2,0,0,1); points[2] = vec4(0, 1, 0,1);
  this->set_points(points); this->set_color(vec4(0.0, 0, 1.0, 1.0));}

vec4 Triangle::get_center()
{
	vec4* p = get_points();
	return vec4((p[0].x + p[1].x + p[2].x)/3, 
				(p[0].y + p[1].y + p[2].y)/3, 
				(p[0].z + p[1].z + p[2].z)/3, 1);
}

vec4 Triangle::get_normal()
{
	vec4* p = get_points();
	vec4 U = p[1] - p[0];
	vec4 V = p[2] - p[0];
	return normalize(cross(U, V));
}

