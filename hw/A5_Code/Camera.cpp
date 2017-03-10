#include "Camera.h"


Camera* Camera::instance=NULL;

Camera::Camera()
{
	view_matrix = mat4();
	prev_prog_size = 0;
}

Camera* Camera::get_instance()
{
	if(!instance)
		instance = new Camera();
	return instance;
}

void Camera::look(vec4 eye, vec4 at, vec4 up)
{
	view_matrix = LookAt(eye, at, up);
	unsigned int i;

	this->eye = eye;
	this->up = up;
	this->at = at;

	u = view_matrix[0];
	v = up;
	n = view_matrix[2];

	if( programs->size() > prev_prog_size )
		for(i = prev_prog_size; i < programs->size(); i++)
			vm_glsl.push_back(glGetUniformLocation((*programs)[i], "view_matrix"));	

	for(i = 0; i < vm_glsl.size(); i++)
		glUniformMatrix4fv(vm_glsl[i], 1, GL_TRUE, view_matrix);		
}
