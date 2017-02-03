#include "InputHandler.h"


void InputHandler::key_funcs(unsigned char key, int x, int y)
{
	
}

void InputHandler:: mouse_click(int button, int state, int x, int y)
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
				}
			}
			else
				lmd = false;
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
			{
				if(!rmd)
				{
					right_click(x, y);
					rmd = true;
				}
				else
					rmd = false;
			}
			break;
	};
}

InputHandler::InputHandler()
{
	lmd = false;
	rmd = false;
	glutKeyboardFunc(key_funcs);
}
