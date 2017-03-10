#version 130

/*
in vec3 fN;
in vec3 fL;
in vec3 fE;


out vec4 fragColor;

uniform vec4 lAmbient, lDiffuse, lSpec;
uniform vec4 mAmbient, mDiffuse, mSpec;
uniform float shininess;

void main() 
{ 
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	vec3 L = normalize(fL);

	vec3 H = normalize(L+E);

	vec4 ambient = lAmbient*mAmbient;
	
	float Kd = max(dot(N, L), 0.0);
	vec4 diffuse = Kd * lDiffuse * mDiffuse;

	float Ks = pow(max(dot(N, H), 0.0), shininess);
	vec4 spec = Ks * lSpec * mSpec;

	if (dot(L, N) < 0.0)
	{
		spec = vec4(0.0, 0.0, 0.0, 1.0);
	}

    fragColor = ambient + diffuse + spec; 
	fragColor.a = 1.0;
} 
*/

in vec4 color;
out vec4 fcolor;

void main()
{
	fcolor = color;
}
