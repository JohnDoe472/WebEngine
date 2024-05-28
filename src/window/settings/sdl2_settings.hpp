#pragma once
#ifndef WEB_ENGINE_WINDOW_SETTINGS_SDL2_SETTINGS_HPP_
#define WEB_ENGINE_WINDOW_SETTINGS_SDL2_SETTINGS_HPP_

#include <string>

#include <glm/glm.hpp>

#include "window/settings/sdl2_window_flags.hpp"

namespace WebEngine::Window::Settings
{
    struct SDL2Settings
    {
        glm::i16vec2 Size = { -1, -1 };

        ESDL2WindowFlags Flags = ESDL2WindowFlags::eSDL2WF_None;

        uint8_t MajorVersionOpenGL = 2;
        uint8_t MinorVersionOpenGL = 0; 
        uint8_t Samples            = 4;
        uint8_t DoubleBuffer       = 1;
        uint8_t DepthSize          = 24;
    };
}

#endif // WEB_ENGINE_WINDOW_SETTINGS_SDL2_SETTINGS_HPP_
