#include "Angel.h"
#include "Circle.h"
#include <math.h>

void Circle::build_shape()
{
	vec4 center = this->get_pos();
	vec4* prev_point = new vec4(center.x + this->get_radius(), 
								center.y, 0, 1) ;
	float incr = 2*M_PI / float(this->get_precision()) ;

	float count = 0.0 ;
	for (int i = 1; i <= this->get_precision(); i++)
	{
		count += incr ;
		vec4* new_point = new vec4(center.x + this->get_radius() * cos(count),
					   			   center.y + this->get_radius() * sin(count), 0, 1) ;	
		Triangle myt = *(new Triangle(this->get_pos(), *prev_point, *new_point));
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

vec4* Circle::get_points()
{
	vec4* my_points = new vec4[3 * this->get_precision()] ;
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
