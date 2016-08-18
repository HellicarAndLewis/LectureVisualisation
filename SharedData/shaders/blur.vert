#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

varying vec2 texCoordVarying;

void main()
{
    texCoordVarying = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();
}