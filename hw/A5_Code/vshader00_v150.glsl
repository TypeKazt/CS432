#version 130

in vec4 vPosition;
in vec4 vNormal;

out vec4 color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform vec4 lightPos;
uniform vec4 lAmbient, lDiffuse, lSpec;
uniform float attenuation;
uniform int enable;

uniform vec4 lightPos2;
uniform vec4 lAmbient2, lDiffuse2, lSpec2;
uniform float attenuation2;
uniform int enable2;
uniform vec4 direction2;
uniform int angle2;

uniform vec4 mAmbient, mDiffuse, mSpec;

uniform float shininess;


void main()
{
	// Transform vertex position into eye coordinates
	float atten = 1.0;
	vec3 pos = (model_matrix * vPosition).xyz;

	vec3 E = normalize( -pos );

	vec3 L1 = normalize( lightPos.xyz - pos );

	vec3 H1 = normalize( L1 + E );


	// Transform vertex normal into eye coordinates
	vec3 N = normalize( model_matrix*vec4(vNormal.xyz, 0.0) ).xyz;
	vec4 color1 = vec4(0.0,0.0,0.0,1.0);
	vec4 color2 = vec4(0.0,0.0,0.0,1.0);

	if (enable2 > 0)
	{
		vec3 L2 = normalize( lightPos2.xyz - pos );
		vec3 H2 = normalize( L2 + E );
		vec3 surfToLightV = normalize(lightPos2.xyz - vPosition.xyz);
		float distToLight = length(lightPos2.xyz - vPosition.xyz);
		atten = 1.0 / (1.0 + attenuation2 * pow(distToLight, 2));

		float lsAngle = degrees(acos(dot(-surfToLightV, normalize(direction2.xyz))));

		vec4 ambient2 = lAmbient2 * mAmbient;

		if(lsAngle > angle2)
		{
			atten = 0.0;
			ambient2 = vec4(0.0,0.0,1.0,1.0);
		}
		else
			ambient2 = vec4(0.0,0.0,1.0,1.0);


		float Kd2 = max( dot(L2, N), 0.0 );
		vec4 diffuse2 = Kd2 * lDiffuse2 * mDiffuse;

		float Ks2 = pow( max(dot(N, H2), 0.0), shininess );
		vec4 specular2 = Ks2 * lSpec2 * mSpec;

		if( dot(L2, N) < 0.0 ) specular2 = vec4(0.0, 0.0, 0.0, 1.0);

		color2 = ambient2 + atten*(diffuse2 + specular2);

	}

	vec4 ambient = lAmbient*mAmbient;

	float Kd = max( dot(L1, N), 0.0 );
	vec4 diffuse = Kd*lDiffuse*mDiffuse;

	float Ks = pow( max(dot(N, H1), 0.0), shininess );
	vec4 specular = Ks * lSpec * mSpec;

	if( dot(L1, N) < 0.0 ) specular = vec4(0.0, 0.0, 0.0, 1.0);

  	gl_Position = proj_matrix * view_matrix * model_matrix * vPosition;

	color1 = ambient + diffuse + specular;
	color = color1 + color2;
	
	color.a = 1.0;
}


