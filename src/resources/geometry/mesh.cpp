#include "resources/geometry/mesh.hpp"

#include "core/parsers/texture_reader.hpp"

#include <iostream>

namespace WebEngine::Resources::Geometry
{
    Mesh::Mesh( const std::vector< Vertex >& vertices, const std::vector< uint32_t >& indices, std::shared_ptr< Material >& material )
    {
        m_defaultMaterial = std::move( material );

        createBuffers( vertices, indices );
    }

    Mesh::~Mesh()
    {
        if ( m_currentMaterial )
            m_currentMaterial = nullptr;
            
        if ( m_defaultMaterial )
            m_defaultMaterial = nullptr;

        if ( m_indexBuffer )
            m_indexBuffer = nullptr;

        if ( m_vertexBuffer )
            m_vertexBuffer = nullptr;
    }

    void Mesh::bind( const Shaders::Shader& shader ) const
    {
        if ( m_vertexBuffer )
            m_vertexBuffer->bind();

        if ( m_indexBuffer )
            m_indexBuffer->bind();

        if ( m_currentMaterial )
            m_currentMaterial->bind( shader );
        else
            m_defaultMaterial->bind( shader );
            
        GLint id = glGetAttribLocation( shader.Id, "vPosition" );
        if ( id != -1 )
        {
            glEnableVertexAttribArray( id );
            glVertexAttribPointer( id, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, Position ) );
        }

        id = glGetAttribLocation( shader.Id, "vTexCoord" );
        if ( id != -1)
        {
            glEnableVertexAttribArray( id );
            glVertexAttribPointer( id, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, TexCoords ) );
        }

        id = glGetAttribLocation( shader.Id, "vNormal" );
        if ( id != -1)
        {
            glEnableVertexAttribArray( id );
            glVertexAttribPointer( id, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, Normals ) );
        }

        id = glGetAttribLocation( shader.Id, "vTanget" );
        if ( id != -1)
        {
            glEnableVertexAttribArray( id );
            glVertexAttribPointer( id, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, Tangent ) );
        }

        id = glGetAttribLocation( shader.Id, "vBitangent" );
        if ( id != -1)
        {
            glEnableVertexAttribArray( id );
            glVertexAttribPointer( id, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, Bitangent ) );
        }
    }

    void Mesh::unbind( const Shaders::Shader& shader ) const
    {
        GLint id = glGetAttribLocation( shader.Id, "vPosition" );
        if ( id != -1 )
            glDisableVertexAttribArray( id );

        id = glGetAttribLocation( shader.Id, "vTexCoord" );
        if ( id != -1)
            glDisableVertexAttribArray( id );

        id = glGetAttribLocation( shader.Id, "vNormal" );
        if ( id != -1)
            glDisableVertexAttribArray( id );

        id = glGetAttribLocation( shader.Id, "vTanget" );
        if ( id != -1)
            glDisableVertexAttribArray( id );

        id = glGetAttribLocation( shader.Id, "vBitangent" );
        if ( id != -1)
            glDisableVertexAttribArray( id );
    }

    void Mesh::createBuffers( const std::vector< Vertex >& vertices, const std::vector< uint32_t >& indices )
    {
        m_vertexCount = vertices.size();

        m_vertexBuffer = std::make_unique< VertexBuffer >( vertices );
        m_indexCount = indices.size();

        m_indexBuffer = std::make_unique< IndexBuffer >( indices );
    }

    void Mesh::draw( const Shaders::Shader& shader ) const
    {
        bind( shader );

        if ( m_indexBuffer )
            glDrawElements( GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr );
        else
            glDrawArrays( GL_TRIANGLES, 0, m_vertexCount );

        unbind( shader );
    }

    const std::shared_ptr< Material >& Mesh::getMaterial() const
    {
        if ( !m_currentMaterial )
            return m_defaultMaterial;

        return m_currentMaterial;
    }
}
