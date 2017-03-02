#ifndef __ALEX_TRIANGLE_H__
#define __ALEX_TRIANGLE_H__

#include "Angel.h"
#include "Shape.h"


class Triangle: public Shape {
    public:
        Triangle(vec4* points);
        Triangle(vec4 p0, vec4 p1, vec4 p2);
        Triangle();

        vec4 get_center();
		vec4 get_normal();
};

#endif
