#include "ConeLight.h"

void ConeLight::set_program(GLuint p)
{
	Light::set_program(p);
	dir_loc = glGetUniformLocation(get_program(), (std::string("direction") + get_id()).c_str());
	angle_loc = glGetUniformLocation(get_program(), (std::string("angle") + get_id()).c_str());
}

void ConeLight::apply_light()
{
	Light::apply_light();
	glUniform4fv(dir_loc, 1, get_direction());
	glUniform1f(angle_loc, get_angle());
}
