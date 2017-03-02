#ifndef __ALEX_POINT_H__
#define __ALEX_POINT_H__

#include "Angel.h"
#include "Shape.h"

class Point: public Shape{
    public:
        Point(vec4 p0): Shape(1)
        { vec4 points[1] = {p0};
          this->set_points(points); this->set_color(vec4(1.0, 0, 0, 1.0));}

        Point(): Shape(1)
        { vec4 points[1]; points[0] = vec4();
          this->set_points(points); 
          this->set_color(vec4(0.0, 0, 1.0, 1.0)); } 
};

#endif
