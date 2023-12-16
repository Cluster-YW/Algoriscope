#version 330 core 
in vec4 vertexColor;
out vec4 FragColor;
void main(){
	float a = (gl_FragCoord.x-200)/1000.0f;
	float b = (gl_FragCoord.y-200)/1000.0f;
	FragColor = vec4(a,b,a,vertexColor.a);
};
