#include "Light.h"

class ConeLight: public Light
{
	public:
		ConeLight(vec4 a, vec4 d, vec4 s, vec4 pos, vec4 dir, float att, float angle): Light(a, d, s, pos, att)
		{
			direction = dir;
			this->angle = angle;
		}

		ConeLight(): Light()
		{
			direction = vec4(0,0,1,0);
			angle = 15.0;
		}

		vec4 get_direction()
		{ return direction; }

		void set_direction(vec4 dir)
		{ direction = dir; }

		float get_angle()
		{ return angle; }

		void set_angle(float a)
		{ angle = a; }

		void set_program(GLuint);
		void apply_light();
	private:
		GLuint dir_loc;
		GLuint angle_loc;

		vec4 direction;
		float angle;

};
