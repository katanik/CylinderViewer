attribute vec4 vertex;
attribute vec3 normal;

varying vec3 vert;
varying vec3 vertNormal;

uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;

void main() {
   vert = vertex.xyz;
   vertNormal = normalMatrix * normal;
   gl_Position = mvpMatrix * vertex;
}
