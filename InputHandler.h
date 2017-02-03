#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include "Angel.h"
#include <map>

typedef void (*KeyFunc)(void);

class InputHandler{
	public:
		void mouse_click(int button, int state, int x, int y);

		void add_key_func(unsigned char key, KeyFunc func)
		{ lfuncs[key] = func; }

		void key_funcs(unsigned char key, int x, int y);

		InputHandler();


	private:
		bool lmd;  // left mouse down
		bool rmd;  // right mouse down
		std::map<unsigned char, KeyFunc> lfuncs;
		virtual void left_click(int x, int y);
		virtual void right_click(int x, int y);

};

#endif
