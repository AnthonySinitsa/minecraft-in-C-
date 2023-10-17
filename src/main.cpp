#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main(){
  if(!glfwInit()){
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
  if(!window){
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if(glewInit() != GLEW_OK){
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  while (!glfwWindowShouldClose(window)){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}