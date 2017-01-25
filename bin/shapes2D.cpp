#include "shapes2D.h"
#include "Angel.h"
#include <math.h>
#include "vec.h"

void Circle::generate_circle()
{
	vec2 center = *(this->get_pos());
	vec2* prev_point = new vec2(center.x + this->get_radius(), 
								center.y) ;
	float incr = M_PI / float(this->get_precision()) ;

	float count = 0.0 ;
	for (int i = 1; i <= this->get_precision(); i++)
	{
		count += incr ;
		vec2* new_point = new vec2(center.x + this->get_radius() * cos(count),
					   			   center.y + this->get_radius() * sin(count)) ;	
		this->_triangles[i-1] = new Triangle2D(this->get_pos(), prev_point, new_point);
		prev_point = new_point;
	}
}

vec2** Circle::get_points()
{
	vec2** my_points = new vec2*[3 * this->get_precision()] ;
	vec2* v = new vec2(1.0, 1.0);
	Triangle2D mt = Triangle2D(v, v, v);
	mt.get_points();
	int count = 0 ;
	for(int i = 0; i < this->get_precision() ; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			my_points[count] = this->_triangles[i]->get_points()[j] ;
			count += 1 ;
		}
	}

	return my_points ;

}
