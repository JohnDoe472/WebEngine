#pragma once
#ifndef WEB_ENGINE_RESOURCES_TEXTURES_TEXTURE_HPP_
#define WEB_ENGINE_RESOURCES_TEXTURES_TEXTURE_HPP_

#include <filesystem>
#include <string>

#include "texture_filtering_mode.hpp"

namespace WebEngine::Resources::Textures
{
    struct TextureInfo
    {
        uint32_t Id;
        int32_t Width;
        int32_t Height;
        int32_t BitsPerPixel;
        ETextureFilteringMode FirstFilter;
        ETextureFilteringMode SecondFilter;
        bool IsMimapped;
    };

    class Texture
    {
    public:
        Texture( std::filesystem::path location, TextureInfo info );
        ~Texture();

        Texture( const Texture& other )             = delete;
        Texture( Texture&& other )                  = delete;
        Texture& operator=( const Texture& other )  = delete;
        Texture& operator=( const Texture&& other ) = delete;

        void bind( uint32_t slot ) const;
        void bindCubeMap( uint32_t slot) const;
        void unbind( uint32_t slot ) const;
        void unbindCubeMap( uint32_t slot ) const;

        const std::filesystem::path& getLocation() const { return m_location; }

    private:
        std::filesystem::path m_location = "";
        TextureInfo m_textureInfo;
    };
}

#endif // WEB_ENGINE_RESOURCES_TEXTURES_TEXTURE_HPP_
