#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

out vec3 ourColor;    // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);   // set the vertex positions
    ourColor = aPos;    // set the output color to the vertex position (to get a gradient effect)
}
