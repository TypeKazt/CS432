#include "Angel.h"
#include "vec.h"
#include "Polyhedron.h"

void Polyhedron::build()
{
	for (unsigned int i = 0; i < this->size; i++)
		this->_triangles[i].build();
}

void Polyhedron::draw()
{
	for (unsigned int i = 0; i < this->size; i++)
		this->_triangles[i].draw();
}

void Polyhedron::setModelMatrix(mat4 mm)
{
	for (unsigned int i = 0; i < this->size; i++)
		this->_triangles[i].setModelMatrix(mm);
}

void Polyhedron::build_shape()
{
	for(unsigned int i = 0; i < size; i++)
	{
		_triangles[i].set_shader(program);
		_triangles[i].set_color(get_color());
	}
}
