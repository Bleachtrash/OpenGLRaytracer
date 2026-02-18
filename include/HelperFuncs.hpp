#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* GetWindow(int window_height, int window_width, char *window_name)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_name, NULL, NULL);
    
    return window;
}

int Init(GLFWwindow* window)
{
    if(!window)
    {
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
    return 0;
}

void ClearBackground(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}