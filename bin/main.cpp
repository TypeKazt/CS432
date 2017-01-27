//SAMPLE CODE

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "shape_h.h"

//Foward declarations of functions
void init();
void display();
void resize(int width, int height);
void keyboard(unsigned char, int, int);
void close();

//objects
vector<Drawable*> objs;
//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#endif

    glutInitWindowSize( 512, 512 );	//set window size to be 512x512 pixels

    glutCreateWindow( "OOP" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
	#ifndef __APPLE__
	GLenum err = glewInit();
	#endif

    init();  //do some initialize for our program

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutWMCloseFunc(close);
	glutReshapeFunc(resize);  //use for recomputing projection matrix on reshape
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}


//Initialization
void init()
{
	srand(time(0));
	GLuint p = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl");
	//make a triangles
	Triangle2D* t1 = new Triangle2D(vec3(-1, -1, 0), vec3(0, -1, 0), vec3(0, 0, 0));
	t1->set_color(vec4(0.0, 0, 1.0, 1.0));
	t1->set_shader(p);
	t1->set_draw_mode(GL_TRIANGLES);
	t1->build();
	objs.push_back(t1);
	
	Circle* c = new Circle();
	c->set_radius(.2);
	c->set_shader(p);
	for (int i = 0; i < 100; i++)
	{
		float r = ((float) rand() / (float)(RAND_MAX))*(1.0);
		float g = ((float) rand() / (float)(RAND_MAX))*(1.0);
		float b = ((float) rand() / (float)(RAND_MAX))*(1.0);
		float o = ((float) rand() / (float)(RAND_MAX))*(1.0);
		vec4* color = new vec4(r, g, b, o);
		c->set_triangle_color(i, *color);
		//c->set_triangle_color(i, vec4(r, g, b, 1.0));
		//c->set_triangle_color(i, vec4(.5, .1, .3, .4));
	}
	c->build();
	objs.push_back(c);

	vec3* sp = new vec3[4];
	sp[0] = vec3(0.6, 0.6, 0);
	sp[1] = vec3(0.9, 0.6, 0);
	sp[2] = vec3(0.9, 0.9, 0);
	sp[3] = vec3(0.6, 0.9, 0);
	Triangle2D* s1 = new Triangle2D(sp[0], sp[1], sp[2]);
	Triangle2D* s2 = new Triangle2D(sp[0], sp[3], sp[2]);
	s1->set_shader(p);
	s2->set_shader(p);
	s1->set_draw_mode(GL_TRIANGLES);
	s2->set_draw_mode(GL_TRIANGLES);
	s1->build();
	s2->build();
	objs.push_back(s1);
	objs.push_back(s2);

	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT);  //clear out the color of the framebuffer and the depth info from the depth buffer
	
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
	case 033:  // Escape key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
}

void close(){
	for (unsigned int i = 0; i < objs.size(); i++)
		delete objs[i];
}

