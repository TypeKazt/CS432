#version 130

in vec4 vPosition;
in vec4 vNormal;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec4 color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform vec4 lightPos;


uniform vec4 lAmbient, lDiffuse, lSpec;
uniform vec4 mAmbient, mDiffuse, mSpec;
uniform float shininess;

void main()
{
	// Transform vertex position into eye coordinates
	vec3 pos = (model_matrix * vPosition).xyz;
	vec3 L = normalize( lightPos.xyz - pos );
	vec3 E = normalize( -pos );
	vec3 H = normalize( L + E );
	/*vec4 mAm= vec4(.5, .2, .1, 1.0);
	vec4 mSp= vec4(.3, .1, .1, 1.0);
	vec4 mDif= vec4(.1, .1, .5, 1.0);*/
	// Transform vertex normal into eye coordinates
	vec3 N = normalize( model_matrix*vec4(vNormal.xyz, 0.0) ).xyz;

	vec4 ambient = lAmbient*mAmbient;

	float Kd = max( dot(L, N), 0.0 );
	vec4 diffuse = Kd*lDiffuse*mDiffuse;

	float Ks = pow( max(dot(N, H), 0.0), shininess );
	vec4 specular = Ks * lSpec * mSpec;

	if( dot(L, N) < 0.0 ) specular = vec4(0.0, 0.0, 0.0, 1.0);

  	gl_Position = proj_matrix * view_matrix * model_matrix * vPosition;

	color = ambient + diffuse + specular;
	if (mAmbient.xyz == vec3(0.0,0.0,0.0)) color = vec4(.5, .2, .1, 1.0);
	
	color.a = 1.0;
}

/*
void main() 
{ 
  	vec3 pos = (view_matrix*model_matrix*vPosition).xyz;
	
	vec3 lightPosInCam = (view_matrix*lightPos).xyz;

	fN = normalize(view_matrix*model_matrix*vNormal).xyz;

	fE = normalize(vec3(0,0,0)-pos.xyz);
	fN=vNormal.xyz;
	fE = vPosition.xyz;
	fL = lightPos.xyz;

	if(lightPos.w != 0.0)
	{
		fL = lightPos.xyz - vPosition.xyz;
	}
	
  	gl_Position = proj_matrix * view_matrix * model_matrix * vPosition;
}
*/



