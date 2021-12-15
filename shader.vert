#version 100 
//COMMENT
attribute vec3 aPos;
attribute vec4 aCol;
attribute vec3 aTexCoord;


varying vec4 ourColor;
varying vec3 texCoord;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   ourColor = aCol;
   texCoord = aTexCoord;
}
