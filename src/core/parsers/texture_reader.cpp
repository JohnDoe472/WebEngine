#include "core/parsers/texture_reader.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <SDL2/SDL_opengles2.h>

namespace fs = std::filesystem;

using namespace WebEngine::Core::Parsers;


TextureReader::TexturePtr TextureReader::loadTexture( fs::path location,
                                                      TextureReader::FilterMode firstFilter,
                                                      TextureReader::FilterMode secondFilter,
                                                      bool generateMipmap, bool flip )
{
    Resources::Textures::TextureInfo info;
    std::string name = location.string();

    glGenTextures( 1, &info.Id );

    stbi_set_flip_vertically_on_load( flip );
    unsigned char* dataBuffer = stbi_load( name.c_str(), &info.Width, &info.Height, &info.BitsPerPixel, STBI_default ); //  STBI_default = 0 = auto channels

    if ( !dataBuffer )
    {
        std::cout << "Can't read image file: " << name << std::endl;
        throw std::runtime_error( "Can't read image file" );
    }

    info.FirstFilter = firstFilter;
    info.SecondFilter = secondFilter;

    GLuint format = GL_RGB;
    switch ( info.BitsPerPixel )
    {
        case 1:
            format = GL_ALPHA;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
            break;
    }

    glBindTexture( GL_TEXTURE_2D, info.Id );

    glTexImage2D( GL_TEXTURE_2D, 0, format, info.Width, info.Height, 0, format, GL_UNSIGNED_BYTE, dataBuffer );

    if ( generateMipmap )
        glGenerateMipmap( GL_TEXTURE_2D );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast< GLint >( firstFilter ) );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast< GLint >( secondFilter ) );

    stbi_image_free( dataBuffer );
    glBindTexture( GL_TEXTURE_2D, 0 );

    TexturePtr newTexture = std::make_unique< Resources::Textures::Texture >( location, info );

    return std::move( newTexture );
}

TextureReader::TexturePtr TextureReader::loadCubemap( std::vector<std::filesystem::path>& faces,
                                                      TextureReader::FilterMode firstFilter,
                                                      TextureReader::FilterMode secondFilter,
                                                      bool flip )
{
    Resources::Textures::TextureInfo info;
    glGenTextures(1, &info.Id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, info.Id);

    info.FirstFilter = firstFilter;
    info.SecondFilter = secondFilter;
    info.IsMimapped = false;

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].string().c_str(), &info.Width, &info.Height, &info.BitsPerPixel, STBI_default);
        GLint format = GL_RGB;
        if ( info.BitsPerPixel == 4 )
            format = GL_RGBA;
    
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, format, info.Width, info.Height, 0, format, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return std::make_unique< Resources::Textures::Texture >( faces[0], info );
}