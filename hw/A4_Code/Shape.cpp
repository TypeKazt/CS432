#include "Shape.h"


Shape::Shape(int n) {
	this->n = n;
	this->vertexLocations = new vec4[n];
	this->colors = new vec4[n];
	this->normals = new vec4[n];
	draw_mode = GL_TRIANGLES;
}

Shape::Shape() {
	draw_mode = GL_TRIANGLE_FAN;
}

void Shape::set_n(int n)
{
	this->n = n;
	vertexLocations = new vec4[n];
	colors = new vec4[n];
	normals = new vec4[n];
}

void Shape::build(){
		long size = n*sizeof(vec4);
		glGenBuffers(1,&VBO);
		glGenVertexArrays(1,&VAO);

		build_shape();  //build the triangle (set the vertex locations and normals)

		//move the data onto the buffer
		glBindVertexArray(VAO);
		glBindBuffer( GL_ARRAY_BUFFER, VBO);
		//glBufferData( GL_ARRAY_BUFFER, size*2,NULL, GL_STATIC_DRAW );
		glBufferData( GL_ARRAY_BUFFER, size,NULL, GL_STATIC_DRAW );
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertexLocations);
		//glBufferSubData(GL_ARRAY_BUFFER, size, size, colors);

		//link the vertex attributes with the buffer
		GLuint vPosition = glGetAttribLocation( program, "vPosition" );
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
/*		GLuint vColor = glGetAttribLocation( program, "vColor" );
		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET((void*)size) );*/
		
}

//on destroy, delete the buffer (cleanup)
Shape::~Shape(){
	glDeleteBuffers(1,&VBO);
	glDeleteVertexArrays(1, &VAO);
}


void Shape::draw(){
	
	glBindVertexArray(VAO);
	glUseProgram(program);

	//set the transformation matrices
	GLuint model_loc = glGetUniformLocation(program,"model_matrix");
	glUniformMatrix4fv(model_loc,1,GL_TRUE,modelmatrix);

	
	GLuint vColor = glGetUniformLocation(program, "color");
	glUniform4fv(vColor, 1, colors[0]);
	

	int size = n * sizeof(vec4);
	//glBufferSubData(GL_ARRAY_BUFFER, size, size, colors);
	
	//draw!
	glDrawArrays(draw_mode,0,n);

}

void Shape::set_points(vec4* points)
{
	for (int i = 0; i < n; i++)
		this->vertexLocations[i] = points[i];	
}

void Shape::set_color(vec4 color)
{
	for(int i = 0; i < n; i++)
		colors[i] = color;
}
