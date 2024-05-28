attribute vec3 vPosition;
attribute vec2 vTexCoord;
attribute vec3 vNormal;

varying vec3 fragPos;
varying vec2 texCoord;
varying vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transposeModel;

void main()
{
    fragPos = vec3(model * vec4(vPosition, 1.0));
    texCoord = vTexCoord;
    normal = mat3(transposeModel) * vNormal;

    gl_Position = projection * view * vec4(fragPos, 1.0);
}