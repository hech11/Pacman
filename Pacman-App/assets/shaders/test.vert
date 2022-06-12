#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;


uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_ViewProj= mat4(1.0f);

out vec2 v_TexCoord;


void main ()
{
	
	gl_Position = u_ViewProj * u_Model * vec4(a_Position, 0.0f, 1.0);
	v_TexCoord = a_TexCoord;
}