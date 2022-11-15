#version 450 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in VS_OUT {
    vec3 texCoords;
} gs_in[];
out vec3 TexCoords; 
	 
void main()
{
    gl_Position = gl_in[0].gl_Position ; 
    TexCoords=vec3(1,0,0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position ; 
    TexCoords=vec3(0,1,0);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position ; 
    TexCoords=vec3(0,0,1);
    EmitVertex();

    EndPrimitive();
}