#ifndef __ALEX_CAMERA_H__
#define __ALEX_CAMERA_H__

#include "Angel.h"
#include <vector>

/*
 * Singleton design pattern to ensure no redundencies.
 * Only a single camera should exist
 */

class Camera
{
	public:
		static Camera* get_instance();
		void look(vec4, vec4, vec4);
		void set_programs(std::vector<GLuint>* v)
		{ programs = v; }


	private:
		std::vector<GLuint>* programs; // shader
		unsigned int prev_prog_size;
		mat4 view_matrix; 
		std::vector<GLuint> vm_glsl; // view matrix for each shader

		Camera();
		static Camera* instance;
};

#endif
