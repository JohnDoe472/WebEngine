#include "resources/textures/texture.hpp"

#include <SDL2/SDL_opengles2.h>

namespace WebEngine::Resources::Textures
{
    Texture::Texture( std::filesystem::path location, TextureInfo info )
        : m_location { location }, m_textureInfo { info }
    {
    }

    Texture::~Texture()
    {
        glDeleteTextures( 1, &m_textureInfo.Id );
    }

    void Texture::bind( uint32_t slot ) const
    {
        glActiveTexture( GL_TEXTURE0 + slot );
        glBindTexture( GL_TEXTURE_2D, m_textureInfo.Id );
    }

    void Texture::bindCubeMap( uint32_t slot ) const
    {
        glActiveTexture( GL_TEXTURE0 + slot );
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_textureInfo.Id );
    }

    void Texture::unbind( uint32_t slot ) const
    {
        glActiveTexture( GL_TEXTURE0 + slot );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    void Texture::unbindCubeMap( uint32_t slot ) const
    {
        glActiveTexture( GL_TEXTURE0 + slot );
        glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
    }
}
