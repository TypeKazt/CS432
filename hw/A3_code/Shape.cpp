#include "Shape.h"
Shape::Shape(int n) {
	this->n = n;
	this->vertexLocations = new vec4[n];
	draw_mode = GL_TRIANGLES;
}

Shape::Shape() {
	draw_mode = GL_TRIANGLE_FAN;
}

void Shape::build(){
		glGenBuffers(1,&VBO);
		glGenVertexArrays(1,&VAO);

		build_shape();  //build the triangle (set the vertex locations and normals)

		//move the data onto the buffer
		glBindVertexArray(VAO);
		glBindBuffer( GL_ARRAY_BUFFER, VBO);
		glBufferData( GL_ARRAY_BUFFER, n*(sizeof(*vertexLocations)),NULL, GL_STATIC_DRAW );
		glBufferSubData(GL_ARRAY_BUFFER, 0, n*sizeof(*vertexLocations), vertexLocations);

		//link the vertex attributes with the buffer
		GLuint vPosition = glGetAttribLocation( program, "vPosition" );
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		
}

//on destroy, delete the buffer (cleanup)
Shape::~Shape(){
	glDeleteBuffers(1,&VBO);
	glDeleteVertexArrays(1, &VAO);
}


void Shape::build_shape(){
	//set up the vertices
	/*
	vertexLocations[0] = vec4(-0.2,0,1);
	vertexLocations[1] = vec4(0.2,0,1);
	vertexLocations[2] = vec4(0,1,1);
	*/
}

void Shape::draw(){
	
	glBindVertexArray(VAO);
	glUseProgram(program);

	//set the transformation matrices
	GLuint model_loc = glGetUniformLocation(program,"model_matrix");
	glUniformMatrix4fv(model_loc,1,GL_TRUE,modelmatrix);

	GLuint vColor = glGetUniformLocation(program, "color");
	glUniform4fv(vColor, 1, color);
	
	//draw!
	glDrawArrays(draw_mode,0,n);

}

void Shape::set_points(vec4* points)
{
	for (int i = 0; i < n; i++)
		this->vertexLocations[i] = points[i];	
}

