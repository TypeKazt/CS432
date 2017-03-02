#include "Sphere.h"

void Sphere::tetrahedron()
{
	vec4 v[4] = {
			vec4(0,0,1,1),
			vec4(0, 2 * sqrt2 / 3, -1.0f / 3.0f, 1),
			vec4(-sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f),
			vec4(sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f)
	};

	divide_triangle(v[0] , v[1], v[2], precision);
	divide_triangle(v[3] , v[2], v[1], precision);
	divide_triangle(v[0] , v[3], v[1], precision);
	divide_triangle(v[0] , v[2], v[3], precision);
}

vec4 Sphere::unit(vec4 p)
{
	float len = p.x*p.x + p.y+p.y + p.z*p.z;
	vec4 t;
	if (len > DivideByZeroTolerance)
	{
		t = p / sqrt(len);
		t.w = 1.0;
	}
	return t;
}

void Sphere::triangle(vec4 a, vec4 b, vec4 c)
{
	vec4 color(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX/ 1.0*rand() / RAND_MAX, 1.0);
	
	set_point(index, a);
	set_vertex_color(index, color);
	index++;

	set_point(index, b);
	set_vertex_color(index, color);
	index++;

	set_point(index, c);
	set_vertex_color(index, color);
	index++;

}

void Sphere::divide_triangle(vec4 a, vec4 b, vec4 c, int count)
{
	if (count > 0)
	{
		vec4 v1 = unit(a + b);
		vec4 v2 = unit(a + c);
		vec4 v3 = unit(b + c);
		divide_triangle(a, v1, v2, count-1);
		divide_triangle(c, v2, v3, count-1);
		divide_triangle(b, v3, v1, count-1);
		divide_triangle(v1, v3, v2, count-1);
	}
	else
		triangle(a, b, c);
}

void Sphere::build_shape()
{
	tetrahedron();
}
