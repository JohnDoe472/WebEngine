#pragma once
#ifndef WEB_ENGINE_RESOURCES_BUFFER_INDEX_BUFFER_HPP_
#define WEB_ENGINE_RESOURCES_BUFFER_INDEX_BUFFER_HPP_

#include <vector>

#include <SDL2/SDL_opengles2.h>

namespace WebEngine::Resources::Buffers
{
    class IndexBuffer
    {
    public:
        IndexBuffer( const uint32_t* data, uint32_t elements )
        {
            glGenBuffers( 1, &m_id );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_id );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, elements * sizeof( uint32_t ), data, GL_STATIC_DRAW );
        }
        IndexBuffer( const std::vector< uint32_t >& data ) : IndexBuffer( data.data(), data.size() ) { }
        ~IndexBuffer() { glDeleteBuffers( 1, &m_id ); }

        IndexBuffer( const IndexBuffer& other )             = delete;
        IndexBuffer( IndexBuffer&& other )                  = delete;
        IndexBuffer& operator=( const IndexBuffer& other )  = delete;
        IndexBuffer& operator=( const IndexBuffer&& other ) = delete;

        void bind() { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_id ); }
        void unbind() { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); }
        uint32_t getID() const { return m_id; }

    private:
        uint32_t m_id = 0;
    };
}

#endif // WEB_ENGINE_RESOURCES_BUFFER_INDEX_BUFFER_HPP_
