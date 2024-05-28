#pragma once
#ifndef WEB_ENGINE_RESOUCES_BUFFER_VERTEX_BUFFER_HPP_
#define WEB_ENGINE_RESOUCES_BUFFER_VERTEX_BUFFER_HPP_

#include <SDL2/SDL_opengles2.h>

namespace WebEngine::Resources::Buffers
{
    template <typename T>
    class VertexBuffer
    {
    public:
        VertexBuffer( const T* data, size_t elements )
        {
            glGenBuffers( 1, &m_id );
            glBindBuffer( GL_ARRAY_BUFFER, m_id );
            glBufferData( GL_ARRAY_BUFFER, elements * sizeof( T ), data, GL_STATIC_DRAW );
        }
        VertexBuffer( const std::vector< T >& data ) : VertexBuffer( data.data(), data.size() ) { }
        ~VertexBuffer() { glDeleteBuffers( 1, &m_id ); }

        VertexBuffer( const VertexBuffer& other )             = delete;
        VertexBuffer( VertexBuffer&& other )                  = delete;
        VertexBuffer& operator=( const VertexBuffer& other )  = delete;
        VertexBuffer& operator=( const VertexBuffer&& other ) = delete;

        void bind() { glBindBuffer( GL_ARRAY_BUFFER, m_id ); }
        void unbind() { glBindBuffer( GL_ARRAY_BUFFER, 0 ); }
        uint32_t getID() const { return m_id; }

    private:
        uint32_t m_id = 0;
    };
}

#endif // WEB_ENGINE_RESOUCES_BUFFER_VERTEX_BUFFER_HPP_
