attribute vec3 vPosition;
attribute vec2 vTexCoord;
attribute vec3 vNormal;
attribute vec3 vTangent;
attribute vec3 vBitangent;

varying vec3 fragPos;
varying vec2 texCoords;
varying vec3 normal;
varying mat3 tbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMatrix;

void main()
{
    tbn = mat3
    (
        normalize( vec3( model * vec4( vTangent,   0.0 ) ) ),
        normalize( vec3( model * vec4( vBitangent, 0.0 ) ) ),
        normalize( vec3( model * vec4( vNormal,    0.0 ) ) )
    );

    fragPos   = vec3( model * vec4( vPosition, 1.0 ) );
    texCoords = vTexCoord;
    normal    = normalize( mat3( normalMatrix ) * vNormal );

    gl_Position = projection * view * vec4( fragPos, 1.0 );
}
