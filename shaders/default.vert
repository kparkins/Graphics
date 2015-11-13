varying vec3 normal;

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    normal = gl_Normal;
    normal = normal + vec3(1, 1, 1);
    normal = vec3(normal.x * .5, normal.y * .5, normal.z * .5);
}