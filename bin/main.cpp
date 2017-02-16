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

//objects
vector<Drawable*> objs;
vector<GLuint> shaders;
bool lmd = false;
bool rmd = false;
bool ron = false;
vec4 zero = vec4(0,0,0,1);
vec4 up = vec4(0,1,0,0);
vec4 center = vec4(0,0,0,1);
GLuint p;

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
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}


//Initialization
void init()
{
	p = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl");
	shaders.push_back(p);
	GLuint pm = glGetUniformLocation(p, "proj_matrix");
	glUniformMatrix4fv(pm,1,GL_TRUE,Perspective(65, 1, 1, 100));	
	Camera::get_instance()->set_programs(&shaders);
	Camera::get_instance()->look(vec4(0,0,0,1), center, up);
	float w2 = .2;
	float xp = 0; 
	float yp = 0; 
	vec4* sp = new vec4[3];
	sp[0] = vec4(xp, yp+w2, 0, 1);
	sp[1] = vec4(xp-w2, yp-w2, 0, 1);
	sp[2] = vec4(xp, yp-w2, 0, 1);
	Triangle* r = new Triangle(sp);
	r->set_shader(p);
	r->set_draw_mode(GL_TRIANGLES);
	r->set_color(vec4(0,0,1,1));
	r->build();
	objs.push_back(r);
	make_polyhedron();

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
    }

}


void close(){
	for (unsigned int i = 0; i < objs.size(); i++)
		delete objs[i];
}

void rotate(int x)
{
	if (ron){
			mat4 ro= mat4(vec4(.9848077, -.1736481, 0), vec4(.1736481, .9848077, 0), vec4(0, 0, 1), vec4(0, 0, 0, 1));
			for (unsigned long i = 0; i < objs.size(); i++)
			{
			/*	vec4 c = objs[i]->get_center();
				mat4 ti = mat4(vec4(1, 0, 0, -c.x), vec4(0, 1, 0, -c.y), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
				mat4 tf = mat4(vec4(1, 0, c.x), vec4(0, 1, c.y), vec4(0, 0, 1), vec4(0, 0, 0, 1));
				mat4 ft = tf * ro * ti;
				ft *= objs[i]->get_model_matrix();
				objs[i]->setModelMatrix(ft);*/
				vec4 new_color = objs[i]->get_color();
				vec4 dc = new_color;
				dc.w = 0;
				dc = normalize(dc);
				if (dot(new_color, new_color) <= dot(zero, zero))
				{
					dc.w = 1;
					new_color = dc;	
				}
				else
					new_color -= dc/100;
				objs[i]->set_color(new_color);
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
				vec4(center.x-sr, center.y, center.z-sr, 1),
				vec4(center.x+sr, center.y, center.z-sr, 1),
				vec4(center.x, center.y-sr, center.z, 1)};
	Triangle* tris = new Triangle[8];

	for(int i = 1; i < 5 ; i++)
		tris[i-1] = Triangle(pt[0], pt[i], pt[i+1]);
	for(int i = 1; i < 5 ; i++)
		tris[3+i] = Triangle(pt[5], pt[i], pt[i+1]);

	Polyhedron* ph = new Polyhedron(tris, 8);
	ph->set_shader(p);
	ph->set_draw_mode(GL_TRIANGLES);
	ph->build();
	objs.push_back(ph);
}
