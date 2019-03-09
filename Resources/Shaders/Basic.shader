#shader vertex
attribute highp vec4 position;
attribute highp vec2 texCoord;
attribute highp vec3 normal;

varying highp vec2 v_TexCoord;
varying highp vec3 v_Normal;
varying highp vec3 v_Position;

uniform mat4 u_MVP;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_MVP * position;
    v_Normal = mat3(u_Model) * normal;
    v_TexCoord = texCoord;
    v_Position = vec4(u_Model * position).xyz;
}

#shader fragment
precision highp float;

varying highp vec3 v_Position;
varying highp vec2 v_TexCoord;
varying highp vec3 v_Normal;

uniform vec4 u_Color;
uniform vec3 u_Light;
uniform vec3 u_Camera;
uniform float u_SpecularStrength;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main()
{
	vec4 texColor = texture2D(u_Texture0, v_TexCoord);

	vec3 ambientLight = vec3(0.1, 0.1, 0.1);

    vec3 posToLightDirVec = normalize(v_Position - u_Light);
    vec3 diffuseColor = vec3( 1.0, 1.0, 1.0);
    float diffuse = clamp(dot(posToLightDirVec, v_Normal), 0.0, 1.0);
    vec3 diffuseFinal = diffuseColor * diffuse;

    vec3 lightToPosDirVec = normalize(u_Light - v_Position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(v_Normal)));
	vec3 posToViewDirVec = normalize(v_Position - u_Camera);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.0), u_SpecularStrength);
	vec3 specularFinal = vec3(1.0, 1.0, 1.0) * specularConstant;

	gl_FragColor  = texColor * u_Color * (vec4(ambientLight, 1.0) + vec4(diffuseFinal, 1.0) + vec4(specularFinal, 1.0));
}