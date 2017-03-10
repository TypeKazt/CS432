#include "Light.h"

void Light::set_program(GLuint p)
{
	program = p;
	light_loc = glGetUniformLocation(program, (std::string("lightPos") + id).c_str());
	ambient_loc = glGetUniformLocation(program, (std::string("lAmbient") + id).c_str());
	diffuse_loc = glGetUniformLocation(program, (std::string("lDiffuse") + id).c_str());
	spec_loc = glGetUniformLocation(program, (std::string("lSpec") + id).c_str());
	att_loc = glGetUniformLocation(program, (std::string("attenuation") + id).c_str());
 	enable_loc = glGetUniformLocation(program, (std::string("enable") + id).c_str());

}

void Light::apply_light()
{
	glUniform4fv(light_loc, 1, get_position());
	glUniform4fv(ambient_loc, 1, get_ambient());
	glUniform4fv(diffuse_loc, 1, get_diffuse());
	glUniform4fv(spec_loc, 1, get_specular());
	glUniform1f(att_loc, get_attenuation());
	glUniform1i(enable_loc, get_enable()); 
}
