#pragma once
#ifndef WEB_ENGINE_CORE_PARSERS_TEXTURE_READER_HPP_
#define WEB_ENGINE_CORE_PARSERS_TEXTURE_READER_HPP_

#include <memory>
#include <filesystem>
#include <vector>

#include "resources/textures/texture.hpp"

namespace WebEngine::Core::Parsers
{
    class TextureReader
    {
        using TexturePtr = std::unique_ptr< Resources::Textures::Texture >;
        using FilterMode = Resources::Textures::ETextureFilteringMode;

    public:
        static TexturePtr loadTexture( std::filesystem::path location,
                                       FilterMode firstFilter = FilterMode::eTFM_Linear,
                                       FilterMode secondFilter = FilterMode::eTFM_Linear,
                                       bool generateMipmap = true, bool flip = false );

        static TexturePtr loadCubemap( std::vector<std::filesystem::path>& faces,
                                       FilterMode firstFilter = FilterMode::eTFM_Linear,
                                       FilterMode secondFilter = FilterMode::eTFM_Linear,
                                       bool flip = false );
    };
}

#endif // WEB_ENGINE_CORE_PARSERS_TEXTURE_READER_HPP_
