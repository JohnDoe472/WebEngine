#include "resources/objects/light_source.hpp"

namespace WebEngine::Resources::Objects
{
    LightSource::LightSource()
    {
        float vertices[] = 
        {
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,

             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,

            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f
        };

        glGenBuffers( 1, &m_vbo );
        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    }

    LightSource::~LightSource()
    {
        glDeleteBuffers( 1, &m_vbo );
    }

    void LightSource::draw( const Shaders::Shader& shader ) const
    {
        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );

        GLint id = glGetAttribLocation( shader.Id, "vPosition" );
        if ( id != -1 )
        {
            glEnableVertexAttribArray( id );
            glVertexAttribPointer( id, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
        }

        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        id = glGetAttribLocation( shader.Id, "vPosition" );
        if ( id != -1 )
            glDisableVertexAttribArray( id );
    }
}
