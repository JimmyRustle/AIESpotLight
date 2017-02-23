#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vPosition;

uniform mat4 cameraWorld;
uniform mat4 projectionViewWorldMatrix;

void main() {

    vNormal = (cameraWorld * vec4(normal,0)).xyz;    
    vPosition = position; 
    //vNormal = normal;	
    vTexCoord = texCoord;
    gl_Position = projectionViewWorldMatrix * (vec4(position,1)); 
}