#version 130

in vec4 vPosition;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

in vec4 vColor;

out vec4 color;  //to send to the fragment shader, interpolated along the way

void main() 
{ 
  gl_Position = proj_matrix*view_matrix*model_matrix*vPosition;
  //gl_Position = view_matrix*model_matrix*vPosition;
  //gl_Position = vec4((model_matrix*vPosition).xy, 0, 1);
  //gl_Position = vec4((proj_matrix*view_matrix*model_matrix*vPosition).xyz , 1);
  color = vColor;  //assign vertex color to the vertex attribute "color".  Will be interpolated during rasterization
}
