#shader vertex
attribute highp vec4 position;

void main()
{
	gl_Position = position;
}

#shader fragment
precision highp float;

uniform vec4 u_Color;

void main()
{
	gl_FragColor = u_Color;
}