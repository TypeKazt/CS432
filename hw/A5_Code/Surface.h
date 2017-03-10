#ifndef __ALEX_SURFACE__
#define __ALEX_SURFACE__
#include "Angel.h"

class Surface
{
	public:
		Surface()
		{   
		ambient = vec4(0, 0, 0, 1.0); diffuse = vec4(0.5, 0.5, 0.5, 1.0); 
		specular = vec4(1.0, 1.0, 1.0, 1.0); shininess = 5.0;
		}   

		Surface(vec4 a, vec4 d, vec4 s, float sh)
		{   
		ambient = a; diffuse = d; 
		specular = s; shininess = sh;
		}

		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		float shininess;
};
#endif
