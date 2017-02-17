//SAMPLE CODE

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "shape_h.h"
#include "Camera.h"

//Foward declarations of functions
void init();
void display();
void resize(int width, int height);
void keyboard(unsigned char, int, int);
void mouse_click(int, int, int, int);
void left_click(int, int);
void right_click(int, int);
void close();
void rotate(int);
void make_polyhedron();
void roll(int);
void pitch(int);
void yaw(int);
void SpecialInput(int, int, int);
void move(int);
void p_mat(int);

//objects
vector<Drawable*> objs;
vector<GLuint> shaders;
bool lmd = false;
bool rmd = false;
bool ron = false;
vec4 zero = vec4(0,0,0,1);
vec4 up = vec4(0,1,0,0);
vec4 center = vec4(0,0,0,1);
GLuint p; // global shader
GLuint pm; //projection matrix
mat4 ro;
float roll_theta = 1.5708;
float pitch_theta = M_PI;
float yaw_theta = M_PI;


//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#endif

    glutInitWindowSize( 500, 500);	//set window size to be 512x512 pixels

    glutCreateWindow( "First Animation" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
	#ifndef __APPLE__
	GLenum err = glewInit();
	#endif

    init();  //do some initialize for our program
	//tini();

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    //glutDisplayFunc( tdisplay );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	//glutMouseFunc(mouse_click);
	glutWMCloseFunc(close);
	glutReshapeFunc(resize);  //use for recomputing projection matrix on reshape
	glutSpecialFunc(SpecialInput);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}


//Initialization
void init()
{
	p = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl");
	shaders.push_back(p);

	pm = glGetUniformLocation(p, "proj_matrix");
	glUniformMatrix4fv(pm,1, GL_TRUE,Perspective(65, 1, 1, 100));	

	Camera::get_instance()->set_programs(&shaders);
	Camera::get_instance()->look(vec4(0,0,0,1), vec4(0,0,-2,1), up);

	srand(time(NULL));
	make_polyhedron();
	ro = mat4(vec4(.988877, 0, 0.149438, 0), 
				  vec4(0, 1, 0, 0), 
				  vec4(-0.149438, 0, .988877, 0), 
				  vec4(0, 0, 0, 1));

	//define color to use when color buffer is cleared
	glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer
	
	for (unsigned int i = 0; i < objs.size(); i++)
		objs[i]->draw();
	
	glFlush();
}

//----------------------------------------------------------------------------

void resize(int w, int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);  //make the viewport the entire window
}

void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 33:  // Escape key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
	case 32: //space 
		ron = !ron;
		rotate(0);
		break;
	case 88: // X
		pitch(-1);
		break;
	case 120: // x
		pitch(1);
		break;	
	case 67: // C
		yaw(1);
		break;
	case 99: // c
		yaw(-1);
		break;
	case 90: // Z
		roll(1);
		break;
	case 122: //z
		roll(-1);
		break;
	case 80: // P
		p_mat(1);
		break;
	case 112: // p
		p_mat(0);
		break;
    }

}

void SpecialInput(int key, int x, int y)
{	
	move(key);
}

void close(){
	for (unsigned int i = 0; i < objs.size(); i++)
		delete objs[i];
}

void rotate(int x)
{
	if (ron){
			for (unsigned long i = 0; i < objs.size(); i++)
			{
				mat4 ti = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 2), vec4(0, 0, 0, 1));
				mat4 tf = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, -2), vec4(0, 0, 0, 1));
				mat4 ft = tf * ro * ti;
				ft *= objs[i]->get_model_matrix();
				objs[i]->setModelMatrix(ft);
			}
			glutPostRedisplay();
			glutTimerFunc(50, rotate, x);
	}
}

void make_polyhedron()
{
	// makes a double sided square pyramid 
	float sr = 0.25;
	vec4 pt[] = {vec4(center.x, center.y+sr, center.z, 1), 
				vec4(center.x-sr, center.y, center.z+sr, 1),
				vec4(center.x+sr, center.y, center.z+sr, 1),
				vec4(center.x+sr, center.y, center.z-sr, 1),
				vec4(center.x-sr, center.y, center.z-sr, 1),
				vec4(center.x, center.y-sr, center.z, 1)};
	Triangle* tris[8];

	for(int i = 1; i < 5 ; i++)
		tris[i-1] = new Triangle(pt[0], pt[i], pt[(i%4)+1]);
	for(int i = 1; i < 5 ; i++)
		tris[3+i] = new Triangle(pt[5], pt[i], pt[(i%4)+1]);

	//Polyhedron* ph = new Polyhedron(*tris, 8);
	//ph->set_shader(p);
	//ph->set_draw_mode(GL_TRIANGLES);
	
	mat4 tranlate = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,-2), vec4(0,0,0,1)); // translate -2 in z
	
	for(int i = 0; i < 8; i++)
	{
		//ph->set_triangle_color(0, vec4(1,0,0,0));
		tris[i]->set_shader(p);
		tris[i]->set_draw_mode(GL_TRIANGLES);
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		tris[i]->set_color(vec4(r,g,b,1));
		tris[i]->setModelMatrix(tranlate);
		tris[i]->build();
		objs.push_back(tris[i]);
	}
/*
	Triangle* wire[8];

	for(int i = 1; i < 5 ; i++)
		wire[i-1] = new Triangle(pt[0], pt[i], pt[(i%4)+1]);
	for(int i = 1; i < 5 ; i++)
		wire[3+i] = new Triangle(pt[5], pt[i], pt[(i%4)+1]);

	//Polyhedron* ph = new Polyhedron(*tris, 8);
	//ph->set_shader(p);
	//ph->set_draw_mode(GL_TRIANGLES);
	
	for(int i = 0; i < 8; i++)
	{
		//ph->set_triangle_color(0, vec4(1,0,0,0));
		tris[i]->set_shader(p);
		tris[i]->set_draw_mode(GL_LINES);
		tris[i]->set_color(vec4(0,0,0,1));
		tris[i]->setModelMatrix(tranlate);
		tris[i]->build();
		objs.push_back(tris[i]);
	}*/
	//ph->build();
	//objs.push_back(ph);
}

void move(int key)
{
	vec4 eye = Camera::get_instance()->get_eye();
	vec4 at = Camera::get_instance()->get_at();
	vec4 up = Camera::get_instance()->get_up();
	vec4 u = Camera::get_instance()->get_u();
	vec4 v = Camera::get_instance()->get_v();
	vec4 f = .1*v;
	vec4 b = -.1*v;
	vec4 l = -.1*u;
	vec4 r = .1*u;
	switch(key)
	{
		case GLUT_KEY_LEFT:
			Camera::get_instance()->look(eye+l, at+l, up);
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			Camera::get_instance()->look(eye+r, at+r, up);
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			Camera::get_instance()->look(eye+f, at+f, up);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			Camera::get_instance()->look(eye+b, at+b, up);
			glutPostRedisplay();
			break;
	}
}

void roll(int dir)
{
	// alter up vector
	float delta = dir*0.1;
	roll_theta += delta;
	Camera::get_instance()->look(Camera::get_instance()->get_eye(), 
								 Camera::get_instance()->get_at(), 
								 vec4(cos(roll_theta), sin(roll_theta), 0 ,0));
	glutPostRedisplay();
}

void pitch(int dir)
{
	// alter at point about x axis
	float delta = dir*0.1;
	pitch_theta += delta;
	vec4 at = Camera::get_instance()->get_at();
	Camera::get_instance()->look(Camera::get_instance()->get_eye(), 
								 vec4(at.x, sin(pitch_theta), cos(pitch_theta), 1),
								 Camera::get_instance()->get_up());
	glutPostRedisplay();

}

void yaw(int dir)
{
	// alter at point about y axiz
	float delta = dir*0.1;
	yaw_theta += delta;
	vec4 at = Camera::get_instance()->get_at();
	Camera::get_instance()->look(Camera::get_instance()->get_eye(), 
								 vec4(sin(yaw_theta), at.y, cos(yaw_theta), 1),
								 Camera::get_instance()->get_up());
	glutPostRedisplay();
}

void p_mat(int type)
{
	
	if(type)
		glUniformMatrix4fv(pm,1, GL_TRUE,Perspective(65, 1, 1, 100));	
	else
		glUniformMatrix4fv(pm,1, GL_TRUE,Frustum(-1, 1, -1, 1, 1, 3));	
	glutPostRedisplay();
}
