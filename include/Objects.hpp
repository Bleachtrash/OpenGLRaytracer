#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Vector.hpp>

// ---------- OPENGL SHAPES ---------- //
struct Triangle
{
    private:
        GLfloat *vertices;
        GLuint VBO;
        GLuint VAO;
        GLuint vertexBuffer;
    public:
        Triangle(){}
        Triangle(Vector2 v_1, Vector2 v_2, Vector2 v_3)
        {
            vertices = new GLfloat[]{
                v_1.x, v_1.y, 0.0f,
                v_2.x, v_2.y, 0.0f,
                v_3.x, v_3.y, 0.0f
            };
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glGenBuffers(1, &vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        }
        void Draw()
        {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);
        }

};
struct Rect
{
    private:
        Triangle tri_1;
        Triangle tri_2;
    public:
        Rect(Vector2 position, float width, float height)
        {
            tri_1 = Triangle(position, position+Vector2(width, 0), position+Vector2(0, -height));
            tri_2 = Triangle(position+Vector2(width, 0), position+Vector2(0, -height), position+Vector2(width, -height));
        }
        void Draw()
        {
            tri_1.Draw();
            tri_2.Draw();
        }
};

// ---------- RayTrace Shapes ---------- //

struct Sphere
{
    Vector3 center;
    float radius;
    Vector3 color;
    Sphere(Vector3 center, float radius, Vector3 color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
    }
    Sphere() : Sphere(Vector3(), 0, Vector3()) {}
};

struct Plane
{
    Vector3 position;
    Vector3 normal;
    Vector3 color;
    Plane(Vector3 position, Vector3 normal, Vector3 color)
    {
        this->position = position;
        this->normal = normal;
        this->color = color;
    }
};