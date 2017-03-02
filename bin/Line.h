#ifndef __ALEX_LINE_H
#define __ALEX_LINE_H

#include "Angel.h"
#include "Shape.h"

class Line: public Shape {
    public:
        Line(vec4* points): Shape(2)
        { this->set_points(points);
          this->set_color(vec4(1.0, 0, 0, 1.0)); }

        Line(vec4 p0, vec4 p1): Shape(2)
        { vec4 points[2] = {p0, p1};
          this->set_points(points);this->set_color(vec4(1.0, 0, 0, 1.0));}

        Line(): Shape(2)
        { vec4 points[2]; points[0] = vec4(-0.2,0,1);
          points[1] = vec4(0.2,0,1); this->set_points(points);
          this->set_color(vec4(0.0, 0, 1.0, 1.0));}

        float get_slope()
        { return (get_points()[0].x - get_points()[1].x) / \
                 (get_points()[0].y - get_points()[1].y); }

        vec4 intersection(Line other);
};

#endif
