#version 140

in vec3 aPos;
out vec3 ourColor;

uniform mat4 u_View;

void main()
{
    gl_Position = u_View * vec4(aPos, 1.0);
    ourColor = vec3(0.5, 0.0, 0.0);  // Set a fixed color to ensure that the shader is working
}
