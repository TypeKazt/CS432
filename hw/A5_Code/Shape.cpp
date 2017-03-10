#include "Shape.h"


Shape::Shape(int n) {
	this->n = n;
	this->vertexLocations = new vec4[n];
	this->colors = new vec4[n];
	this->normals = new vec4[n];
	draw_mode = GL_TRIANGLES;
	surf = Surface();
}

Shape::Shape() {
	draw_mode = GL_TRIANGLES;
	surf = Surface();
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

		build_shape();  

		//move the data onto the buffer
		glBindVertexArray(VAO);
		glBindBuffer( GL_ARRAY_BUFFER, VBO);
		glBufferData( GL_ARRAY_BUFFER, size*2,NULL, GL_STATIC_DRAW );
		//glBufferData( GL_ARRAY_BUFFER, size,NULL, GL_STATIC_DRAW );
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertexLocations);
		glBufferSubData(GL_ARRAY_BUFFER, size, size, normals);
		//glBufferSubData(GL_ARRAY_BUFFER, size, size, colors);

		//link the vertex attributes with the buffer
		vPosition = glGetAttribLocation( program, "vPosition" );
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		vNormal = glGetAttribLocation( program, "vNormal" );
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );

		diffuse_loc = glGetUniformLocation( program, "mDiffuse" );
		spec_loc = glGetUniformLocation( program, "mSpec" );
		ambient_loc = glGetUniformLocation( program, "mAmbient" );
		alpha_loc = glGetUniformLocation( program, "shininess" );
		
		model_loc = glGetUniformLocation(program,"model_matrix");

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
 	vec4 mAm= vec4(.5, .2, .1, 1.0);
    vec4 mSp= vec4(.3, .1, .1, 1.0);
    vec4 mDif= vec4(.1, .1, .5, 1.0);
    //set the transformation matrices
	glUniformMatrix4fv(model_loc,1,GL_TRUE,modelmatrix);
	/*glUniform4fv(diffuse_loc,1,surf.diffuse);
	glUniform4fv(spec_loc,1,surf.specular);
	glUniform4fv(ambient_loc,1,surf.ambient);
	glUniform1f(alpha_loc, surf.shininess);*/

	glUniform4fv(diffuse_loc,1,mDif);
	glUniform4fv(spec_loc,1,mSp);
	glUniform4fv(ambient_loc,1,mAm);
	glUniform1f(alpha_loc, .5);


	/*GLuint light_loc = glGetUniformLocation(program, "lightPos");
    GLuint ambient_loc = glGetUniformLocation(program, "lAmbient");
    GLuint diffuse_loc = glGetUniformLocation(program, "lDiffuse");
    GLuint spec_loc = glGetUniformLocation(program, "lSpec");
	
	glUniform4fv(light_loc, 1, vec4(0,2,1,1));
    glUniform4fv(ambient_loc, 1, vec4(.1, .2, .5, 1));
    glUniform4fv(diffuse_loc, 1, vec4(.5, .2, .1, 1));
    glUniform4fv(spec_loc, 1, vec4(1,1,1,1));*/


/*	
	GLuint vColor = glGetUniformLocation(program, "color");
	glUniform4fv(vColor, 1, colors[0]);*/
	

	//int size = n * sizeof(vec4);
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
