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
			
in vec3 v_Position;
in vec2 v_TexCoord;
in vec3 v_Normal;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec3 u_Light;
uniform vec3 u_Camera;
uniform float u_SpecularStrength;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main()
{
    vec4 texColor = texture(u_Texture0, v_TexCoord);

    vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);

    vec3 posToLightDirVec = normalize(v_Position - u_Light);
    vec3 diffuseColor = vec3( 1.f, 1.f, 1.f );
    float diffuse = clamp(dot(posToLightDirVec, v_Normal), 0.f, 1.f);
    vec3 diffuseFinal = diffuseColor * diffuse;

	vec3 lightToPosDirVec = normalize(u_Light - v_Position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(v_Normal)));
	vec3 posToViewDirVec = normalize(v_Position - u_Camera);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.f), u_SpecularStrength);
	vec3 specularFinal = vec3(1.f, 1.f, 1.f) * specularConstant;

    color = texColor * u_Color * (vec4(ambientLight, 1.0f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
};;