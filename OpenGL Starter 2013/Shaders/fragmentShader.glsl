#version 430

uniform vec4 color;
in vec4 vertColor;

void main()
{
	gl_FragColor = color * vertColor;
}