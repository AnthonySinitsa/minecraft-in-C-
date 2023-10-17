#version 330 core
out vec4 FragColor;   // output color of the pixel

in vec3 ourColor;    // received color from the vertex shader

void main()
{
    FragColor = vec4(ourColor, 1.0);   // set the output color to the received color
}
