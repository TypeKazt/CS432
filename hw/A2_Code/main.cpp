//SAMPLE CODE

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "shape_h.h"

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

//objects
vector<Drawable*> objs;
bool lmd = false;
bool rmd = false;
bool ron = false;
vec4 zero = vec4(0,0,0,1);
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

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutMouseFunc(mouse_click);
	glutWMCloseFunc(close);
	glutReshapeFunc(resize);  //use for recomputing projection matrix on reshape
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}

void left_click(int x, int y)
{
	float w2 = .2;
	float xp = ((float)x-249) / 249; 
	float yp = -((float)y-249) / 249; 
	vec3* sp = new vec3[4];
	sp[0] = vec3(xp+w2, yp+w2, 1);
	sp[1] = vec3(xp-w2, yp+w2, 1);
	sp[2] = vec3(xp-w2, yp-w2, 1);
	sp[3] = vec3(xp+w2, yp-w2, 1);
	Rectangle* r ;
	r = new Rectangle(sp);
	r->set_shader(p);
	r->set_draw_mode(GL_TRIANGLE_STRIP);
	r->build();
	objs.push_back(r);
	glutPostRedisplay();

}

void right_click(int x, int y)
{
	float w2 = .2;
	float xp = ((float)x-249) / 249; 
	float yp = -((float)y-249) / 249; 
	vec3* sp = new vec3[3];
	sp[0] = vec3(xp, yp+w2, 1);
	sp[1] = vec3(xp-w2, yp-w2, 1);
	sp[2] = vec3(xp, yp-w2, 1);
	Triangle2D* r = new Triangle2D(sp);
	r->set_shader(p);
	r->set_draw_mode(GL_TRIANGLES);
	r->set_color(vec4(0,0,1,1));
	r->build();
	objs.push_back(r);
	glutPostRedisplay();

}

//Initialization
void init()
{
	srand(time(0));
	p = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl");
	//make a triangles
	/*
	Triangle2D* t1 = new Triangle2D(vec3(-1, -1, 0), vec3(0, -1, 0), vec3(0, 0, 0));
	t1->set_color(vec4(0.0, 0, 1.0, 1.0));
	t1->set_shader(p);
	t1->set_draw_mode(GL_TRIANGLES);
	t1->build();
	objs.push_back(t1);*/
/*
	Rectangle* r ;
	r = new Rectangle(make_square_p());
	//*r = Rectangle::build_sqaure(vec3(.5,0,1), .2);
	r->set_shader(p);
	r->set_draw_mode(GL_TRIANGLE_STRIP);
	r->build();
	objs.push_back(r);*/

/*
	Triangle2D* s1 = new Triangle2D(sp[0], sp[1], sp[2]);
	s1->set_shader(p);
	s1->set_draw_mode(GL_TRIANGLE_FAN);
	s1->build();*/
	//objs.push_back(s1);

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
	case 32: //space 
		ron = !ron;
		rotate(0);
		break;
    }

}

void mouse_click(int button, int state, int x, int y)
{
	switch(button)
      {   
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
              {
                  if (!lmd)
                  {
                      left_click(x, y); 
                      lmd = true;
                      rmd = false;
                  }
					  glutDetachMenu(GLUT_RIGHT_BUTTON);
              }
              else
			  {
                  lmd = false;
				  glutAttachMenu(GLUT_LEFT_BUTTON);
			  }
              break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
              {
                  if(!rmd)
                  {
					right_click(x, y); 
                      rmd = true;
                  	  lmd = false;
                  }
                  
              }
			else
			{
            	rmd = false;
			}
              break;
		
      };  
}

void close(){
	for (unsigned int i = 0; i < objs.size(); i++)
		delete objs[i];
}

void rotate(int x)
{
	if (ron){
			mat3 ro= mat3(vec3(.9848077, -.1736481, 0), vec3(.1736481, .9848077, 0), vec3(0, 0, 1));
			for (unsigned long i = 0; i < objs.size(); i++)
			{
				vec3 c = objs[i]->get_center();
				mat3 ti = mat3(vec3(1, 0, -c.x), vec3(0, 1, -c.y), vec3(0, 0, 1));
				mat3 tf = mat3(vec3(1, 0, c.x), vec3(0, 1, c.y), vec3(0, 0, 1));
				mat3 ft = tf * ro * ti;
				ft *= objs[i]->get_model_matrix();
				objs[i]->setModelMatrix(ft);
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
