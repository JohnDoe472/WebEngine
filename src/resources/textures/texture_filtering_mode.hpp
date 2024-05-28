#pragma once
#ifndef WEB_ENGINE_RESOURCES_TEXTURES_FILTERIG_MODE_HPP_
#define WEB_ENGINE_RESOURCES_TEXTURES_FILTERIG_MODE_HPP_

namespace WebEngine::Resources::Textures
{
    enum class ETextureFilteringMode
    {
        eTFM_Nearest               = 0x2600,
        eTFM_Linear                = 0x2601,
        eTFM_NearestMipmap_Nearest = 0x2700,
        eTFM_LinearMipmapLinear    = 0x2703,
        eTFM_LinearMipmapNearest   = 0x2701,
        eTFM_NearestMipmapLinear   = 0x2702
    };
}

#endif // WEB_ENGINE_RESOURCES_TEXTURES_FILTERIG_MODE_HPP_
