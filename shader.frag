#version 100 
//COMMENT
//attribute vec4 ourColor;
//attribute vec3 texCoord;

precision highp float;

varying vec4 ourColor;
varying vec3 texCoord;

uniform sampler2D ourTexture;
uniform int isText;

void main()
{
	if(isText == 0)
	{
		vec4 texColor = texture2D(ourTexture, texCoord.xy) * texCoord.z;
		gl_FragColor = ourColor * (1.0 - texCoord.z) + texColor;
					
	}
	else
	{
		vec4 texColor = texture2D(ourTexture, texCoord.xy);
  	gl_FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, ourColor.w * texColor.x);
	}
}
