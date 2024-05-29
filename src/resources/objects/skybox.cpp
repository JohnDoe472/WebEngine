#include "skybox.hpp"
#include "core/parsers/texture_reader.hpp"

#include <iostream>

using namespace WebEngine::Resources::Objects;

Skybox::Skybox( std::vector<std::filesystem::path> cubemapFacesPaths )
{
    loadCubemap( cubemapFacesPaths );
}

Skybox::~Skybox()
{
    if ( m_cubemap )
        m_cubemap = nullptr;
}

void Skybox::draw( const Shaders::Shader& shader ) const
{
    shader.setInt("skybox", 0);
    m_cubemap->bindCubeMap( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );

    GLint id = glGetAttribLocation( shader.Id, "aPos" );
    if ( id != -1 )
    {
        glEnableVertexAttribArray( id );
        glVertexAttribPointer( id, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
    }

    glDrawArrays( GL_TRIANGLES, 0, 36 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    id = glGetAttribLocation( shader.Id, "aPos" );
    if ( id != -1 )
        glDisableVertexAttribArray( id );

    m_cubemap->unbindCubeMap( 0 );
}

void Skybox::loadCubemap( std::vector<std::filesystem::path> cubemapFacesPaths )
{
    using namespace WebEngine::Core::Parsers;
    m_cubemap = TextureReader::loadCubemap( cubemapFacesPaths, 
                                            Textures::ETextureFilteringMode::eTFM_Linear, 
                                            Textures::ETextureFilteringMode::eTFM_Linear, 
                                            false);

    initVBO();
}

void Skybox::initVBO() {
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
