#version 140

in vec3 aPos;
out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = vec3(0.5, 0.0, 0.0);  // Set a fixed color to ensure that the shader is working
}
