#include "Shape.h"
#include "Angel.h"
#include "Triangle.h"
#include <math.h>

class Sphere: public Shape
{
	public:
		Sphere(): Shape()
		{ precision = 4; sqrt2 = sqrt(2); sqrt6 = sqrt(6); index = 0; radius = 1.0;}

		void set_precision(unsigned short p)
		{ this->precision = p; }

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
		void divide_triangle(vec4, vec4, vec4, int);
		void triangle(vec4, vec4, vec4);
		vec4 unit(vec4);
		void build_shape();
};
