#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdio.h>
#include <Objects.hpp>
#include <HelperFuncs.hpp>

struct Shader
{
    GLuint program;
    Shader(const char* vertex_shader, const char* fragment_shader)
    {
        program = LoadShaders(vertex_shader, fragment_shader);
    }
    void use()
    {
        glUseProgram(program);
    }
    void setFloat(const char* name, const float value);
    void setFloat2(const char* name, const float value1, const float value2);
    void setFloat3(const char* name, const float value1, const float value2, const float value3);
    
    void setInt(const char* name, const int value);

    void setSphere(const char* name, Sphere value);
    void setPlane(const char* name, Plane value);
    void makeLightGrid(int w, int h, Vector3 centerPos);
};

void Shader::setFloat(const char* name, const float value)
{
    glUniform1f(glGetUniformLocation(this->program, name), value);
}
void Shader::setFloat2(const char* name, const float value1, const float value2)
{
    glUniform2f(glGetUniformLocation(this->program, name), value1, value2);

}
void Shader::setFloat3(const char* name, const float value1, const float value2, const float value3)
{
    glUniform3f(glGetUniformLocation(this->program, name), value1, value2, value3);

}

void Shader::setInt(const char* name, const int value)
{
    glUniform1i(glGetUniformLocation(this->program, name), value);
}

void Shader::setSphere(const char* name, Sphere value)
{
    char* position = new char[strlen(name) + strlen(".position") + 1];
    strcpy(position, name);
    strcat(position, ".position\0");
    char* radius = new char[strlen(name) + strlen(".radius") + 1];
    strcpy(radius, name);
    strcat(radius, ".radius\0");
    char* color = new char[strlen(name) + strlen(".color") + 1];
    strcpy(color, name);
    strcat(color, ".color\0");
    char* roughness = new char[strlen(name) + strlen(".roughness") + 1];
    strcpy(roughness, name);
    strcat(roughness, ".roughness\0");

    this->setFloat3(position, value.center.x, value.center.y, value.center.z);
    this->setFloat(radius, value.radius);
    this->setFloat3(color, value.color.x, value.color.y, value.color.z);
    this->setFloat(roughness, value.roughness);
}
void Shader::setPlane(const char* name, Plane value)
{
    char* position = new char[strlen(name) + strlen(".position") + 1];
    strcpy(position, name);
    strcat(position, ".position\0");
    char* normal = new char[strlen(name) + strlen(".normal") + 1];
    strcpy(normal, name);
    strcat(normal, ".normal\0");
    char* color = new char[strlen(name) + strlen(".color") + 1];
    strcpy(color, name);
    strcat(color, ".color\0");
    char* roughness = new char[strlen(name) + strlen(".roughness") + 1];
    strcpy(roughness, name);
    strcat(roughness, ".roughness\0");

    this->setFloat3(position, value.position.x, value.position.y, value.position.z);
    this->setFloat3(normal, value.normal.x, value.normal.y, value.normal.z);
    this->setFloat3(color, value.color.x, value.color.y, value.color.z);
    this->setFloat(roughness, value.roughness);
}