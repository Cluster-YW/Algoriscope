#version 330 core
layout(location = 0) in vec3 aPos;
<<<<<<< HEAD
void main(){
    gl_Position = vec4(aPos,1.0);
=======
uniform mat4 projection;
uniform mat4 translation;
void main(){
    gl_Position = projection*translation*vec4(aPos,1.0);
>>>>>>> 840ed39b2fbc8c7a772eb5af67975486e45b7dab
};
// #version 330 core
// layout(location= 0 )in vec3 aPos;
// layout(location = 1) in vec3 aColor;
// out vec4 vertexColor;
// uniform float change;
// void main()
// {
// 	gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);
//     vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0);
// };//用另一种语言GLSL编写顶点着色器