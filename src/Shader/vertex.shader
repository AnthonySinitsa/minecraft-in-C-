#version 140

in vec3 aPos;
out vec3 ourColor;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);  // Updated the multiplication order
    ourColor = vec3(0.5, 0.0, 0.0);  // Keep the fixed color for now
}
