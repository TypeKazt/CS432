#include "shapes2D.h"
#include "Angel.h"

using namespace std;

int main()
{
	vec2* pos = new vec2(10.0, 10.0);
	float rad = 5.0;
	Circle c = Circle(pos, rad, 100);
	c.generate_circle();
	vec2** points = c.get_points();
	for (int i = 0; i < 300; i++)
		std::cout << *(points[i]) << std::endl;
}
