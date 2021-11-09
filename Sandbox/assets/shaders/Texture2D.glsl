#type vertex

#version 450 core

layout(location=0) in vec3 a_Position;
layout(location=1) in vec4 a_Color;
layout(location=2) in vec2 a_TexCoord;
			
uniform mat4 u_ViewProjection;

struct VertexOutput 
{
	vec4 Color;
	vec2 TexCoord;
};

layout(location=0) out VertexOutput Output;

void main()
{
	Output.Color = a_Color;
	Output.TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * vec4(a_Position,1.0);
}

#type fragment
#version 450 core

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
};

layout(location=0) out vec4 color;

layout(location=0) in VertexOutput Input;

void main()
{
	color = Input.Color;
}