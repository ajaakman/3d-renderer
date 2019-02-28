#shader vertex
attribute highp vec4 position;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
}

#shader fragment
precision highp float;

uniform vec4 u_Color;

void main()
{
	gl_FragColor = u_Color;
}