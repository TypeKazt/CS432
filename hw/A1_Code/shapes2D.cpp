#include "shapes2D.h"
#include "Angel.h"
#include <math.h>
#include "vec.h"

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
