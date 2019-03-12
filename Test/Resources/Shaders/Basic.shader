#shader vertex
#version 330 core
			
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Position;

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
#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float specularFocus;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 v_Position;
in vec2 v_TexCoord;
in vec3 v_Normal;

layout(location = 0) out vec4 color;

uniform Material material;

uniform vec4 u_Color;
uniform vec3 u_Light;
uniform vec3 u_Camera;

void main()
{
	vec4 texColor = texture(material.diffuseTex, v_TexCoord);
	vec4 texColorSpec = texture(material.specularTex, v_TexCoord);

    vec3 posToLightDirVec = normalize(u_Light - v_Position);
    float diffuse = clamp(dot(posToLightDirVec, v_Normal), 0.f, 1.f);
    vec3 diffuseFinal = material.diffuse * diffuse;

	vec3 lightToPosDirVec = normalize(v_Position - u_Light);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(v_Normal)));
	vec3 posToViewDirVec = normalize(u_Camera - v_Position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.f), material.specularFocus);
	vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, v_TexCoord).rgb;

    color = texColor * u_Color * (vec4(material.ambient, 1.0f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
};;