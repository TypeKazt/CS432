#version 130

in vec3 vPosition;
uniform mat3 model_matrix;

in vec4 vColor;

out vec4 color;  //to send to the fragment shader, interpolated along the way

void main() 
{ 
  gl_Position = vec4((model_matrix*vPosition).xy, 0,1);
  color = vColor;  //assign vertex color to the vertex attribute "color".  Will be interpolated during rasterization
}
