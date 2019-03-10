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

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float specularStrength;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

varying highp vec3 v_Position;
varying highp vec2 v_TexCoord;
varying highp vec3 v_Normal;

uniform Material material;

uniform vec4 u_Color;
uniform vec3 u_Light;
uniform vec3 u_Camera;

void main()
{
	vec4 texColor = texture2D(material.diffuseTex, v_TexCoord);

    vec3 posToLightDirVec = normalize(v_Position - u_Light);
    float diffuse = clamp(dot(posToLightDirVec, v_Normal), 0.0, 1.0);
    vec3 diffuseFinal = material.diffuse * diffuse;

    vec3 lightToPosDirVec = normalize(u_Light - v_Position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(v_Normal)));
	vec3 posToViewDirVec = normalize(v_Position - u_Camera);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.0), material.specularStrength);
	vec3 specularFinal = material.specular * specularConstant;

	gl_FragColor  = texColor * u_Color * (vec4(material.ambient, 1.0) + vec4(diffuseFinal, 1.0) + vec4(specularFinal, 1.0));
}