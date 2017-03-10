#include "Angel.h"

class Light
{
	public:

		Light()
          {
              ambient = vec4(0, 0, 0, 1.0); diffuse = vec4(0.5, 0.5, 0.5, 1.0);
              specular = vec4(1.0, 1.0, 1.0, 1.0); position = vec4(0.0, 0.0, 0.0, 0.0);
			  attenuation = 1.0; enabled = 1.0;
			  id = std::string("");
          }

		Light(vec4 a, vec4 d, vec4 s, vec4 p, float att)
          {
			  ambient = a;  diffuse = d;
              specular = s; position = p;
			  attenuation = att; enabled = 1.0;
			  id = std::string("");
          }

		vec4 get_ambient()
          { return ambient; }

        void set_ambient(vec4 a)
          { ambient = a; }

        vec4 get_diffuse()
          { return diffuse; }

        void set_diffuse(vec4 d)
          { diffuse = d; }

        vec4 get_specular()
          { return specular; }

        void set_specular(vec4 s)
          { specular = s; }

        vec4 get_position()
          { return position; }

        void set_position(vec4 p)
          { position = p; }

		float get_attenuation()
		{ return attenuation; }

		void set_attenuation(float att)
		{ attenuation = att; }

		int get_enable()
		{ return enabled; }

		void set_enable(int e)
		{ enabled = e; }

		std::string get_id()
		{ return id; }

		void set_id (std::string id)
		{ this->id = id; }

		virtual void set_program(GLuint);
		GLuint get_program()
		{ return program; }

		virtual void apply_light();

	private:
          vec4 ambient;
          vec4 diffuse;
          vec4 specular;
          vec4 position;

		  GLuint program;
		  GLuint light_loc;
		  GLuint ambient_loc;
		  GLuint diffuse_loc;
		  GLuint spec_loc;
		  GLuint att_loc;
		  GLuint enable_loc;

		  float attenuation;
		  int enabled;
		  std::string id;
};
