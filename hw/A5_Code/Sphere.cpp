#include "Sphere.h"

Sphere::Sphere(): Shape()
{ 
	precision = 4; sqrt2 = sqrt(2); sqrt6 = sqrt(6); index = 0; radius = 1.0;
	set_n((int)pow(4, precision+1)*3);
}

void Sphere::set_precision(unsigned short p)
{
	precision = p;
	set_n((int)pow(4, p+1)*3);
}


void Sphere::tetrahedron()
{
	vec4 v[4] = {
			vec4(0.0f,0.0f,1.0f,1.0f),
			vec4(0.0f, 2.0f * sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f),
			vec4(-sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f),
			vec4(sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f)
	};

	divide_triangle(v[0] , v[1], v[2], precision);
	divide_triangle(v[3] , v[2], v[1], precision);
	divide_triangle(v[0] , v[3], v[1], precision);
	divide_triangle(v[0] , v[2], v[3], precision);
}

vec4 Sphere::unit(const vec4& p)
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

void Sphere::triangle(const vec4& a, const vec4& b, const vec4& c)
{
	vec4 color(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX/ 1.0*rand() / RAND_MAX, 1.0);
	Triangle myt = Triangle(a,b,c);
	vec4 norm = myt.get_normal();
	
	set_point(index, a);
	set_vertex_color(index, color);
	this->set_normal(index, norm);
	index++;

	set_point(index, b);
	set_vertex_color(index, color);
	this->set_normal(index, norm);
	index++;

	set_point(index, c);
	set_vertex_color(index, color);
	this->set_normal(index, norm);
	index++;

}

void Sphere::divide_triangle(const vec4& a, const vec4& b, const vec4& c, int count)
{
	if (count > 0)
	{
		vec4 v1 = this->unit(a + b);
		vec4 v2 = this->unit(a + c);
		vec4 v3 = this->unit(b + c);
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
