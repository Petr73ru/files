#version 130
attribute vec3 aPos;
attribute vec3 aColor;

uniform vec2 offSet;

out vec3 ourColor;

void main()
{
  gl_Position = vec4(aPos.x + offSet.x, -aPos.y, aPos.z, 1.0);
  ourColor = aPos;
}
