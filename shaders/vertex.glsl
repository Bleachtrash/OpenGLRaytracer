#version 400

in vec4 position;
out vec2 fragPos;

void main()
{
    gl_Position = position;
    fragPos = position.xy;    
}