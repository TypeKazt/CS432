#include "Shape.h"
#include "Angel.h"
#include "Triangle.h"
#include <math.h>

class Sphere: public Shape
{
	public:
		Sphere();

		void set_precision(unsigned short);

		void set_radius(float r)
		{ radius = r; }

		float get_radius()
		{ return radius; }

	private:
		int index; // for indexing vertecies when generating spehere
		unsigned short precision;
		float sqrt2, sqrt6;
		float radius;
		void tetrahedron();
		void divide_triangle(const vec4&, const vec4&, const vec4&, int);
		void triangle(const vec4&, const vec4&, const vec4&);
		vec4 unit(const vec4&);
		void build_shape();
};
