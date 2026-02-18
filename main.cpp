#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <HelperFuncs.hpp>
#include <stdio.h>
#include <Shader.hpp>
#include <Objects.hpp>
#include <math.h>
#include <vector>
#include <string>

#define PI 3.1415926535898
int main()
{
    glfwInit();
    GLFWwindow *window = GetWindow(600, 600, "HELLO WINDOW");
    Init(window);

    Shader shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    Rect plane = Rect(Vector2(-1, 1), 2, 2);

    float fov = 45;
    float fovRads = fov * PI/180;
    float cameraDistance = 1.0/tan(fovRads/2);
    Vector3 lightPos(0, 0, 0);

    std::vector<Sphere> spheres = {
        Sphere(Vector3(0, 0, 0), 0.25, Vector3(1, 1, 1), 0.25)};
    std::vector<Plane> planes = {
        Plane(Vector3(0, -0.25, 0), Vector3(0, 1, 0), Vector3(1, 1, 1), 1),    // Ground
        Plane(Vector3(0, 0, -1.25), Vector3(0, 0, 1), Vector3(1, 1, 1), 1),     // Back wall
        Plane(Vector3(0, 1, 0), Vector3(0, -1, 0), Vector3(1, 1, 1), 1),       // Ceiling
        Plane(Vector3(0, 0, 1.25), Vector3(0, 0, -1), Vector3(1, 1, 1), 1),     // Front wall
        Plane(Vector3(-1.25, 0, 0), Vector3(1, 0, 0), Vector3(1, 0, 0), 1),    // Left wall
        Plane(Vector3(1.25, 0, 0), Vector3(-1, 0, 0), Vector3(0, 1, 0), 1)};   // Right wall

    while(!glfwWindowShouldClose(window))
    {
        ClearBackground(0.2f, 0.3f, 0.3f, 1.0f);

        shader.use();

        shader.setInt("sphereCount", spheres.size());
        for(int i = 0; i < spheres.size(); i++)
        {
            char *sphereName = new char[strlen("spheres[]") + strlen(std::to_string(i).c_str()) + 1];
            strcpy(sphereName, "spheres[");
            strcat(sphereName, std::to_string(i).c_str());
            strcat(sphereName, "]\0");
            shader.setSphere(sphereName, spheres[i]);
        }
        shader.setInt("planeCount", planes.size());
        for(int i = 0; i < planes.size(); i++)
        {
            char *planeName = new char[strlen("planes[]") + strlen(std::to_string(i).c_str()) + 1];
            strcpy(planeName, "planes[");
            strcat(planeName, std::to_string(i).c_str());
            strcat(planeName, "]\0");
            shader.setPlane(planeName, planes[i]);
        }

        shader.setFloat3("cameraPos", 0, 0, cameraDistance);
        shader.setFloat3("lightPos", lightPos.x, lightPos.y, lightPos.z);
        plane.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        lightPos.x = sin(glfwGetTime());
        lightPos.z = cos(glfwGetTime());
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}