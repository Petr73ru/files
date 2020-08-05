#version 130
out vec4 FragColor;
in vec3 ourColor;

void main()
{
  FragColor = vec4(ourColor.x + 0.5f, ourColor.y + 0.5f, ourColor.b + 0.5f, 1.0);
}
