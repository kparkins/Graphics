varying vec3 normal;
uniform sampler2D texture;

void main() {
    gl_FragColor = texture2D(texture, gl_TexCoord[0].st);
    gl_FragColor = vec4(normal.x, normal.y, normal.z, gl_FragColor.x);
}