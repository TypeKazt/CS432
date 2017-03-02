#include "Line.h"
#include "Angel.h"


//TODO needs to be fixed
vec4 Line::intersection(Line other)
{
	const vec4 r = vec4(1, get_slope(), 1);
	const vec4 s = vec4(1, other.get_slope(), 1);
	const vec4 p = get_points()[0];
	const vec4 q = other.get_points()[0];
//	vec4 t = cross(q-p, s)/cross(r, s);
	return p;
}
