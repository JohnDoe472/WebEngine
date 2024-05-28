#pragma once
#ifndef WEB_ENGINE_WINDOW_INPUT_KEY_STATE_HPP_
#define WEB_ENGINE_WINDOW_INPUT_KEY_STATE_HPP_

namespace WebEngine::Window::Input
{
    enum class EKeyState
    {
        eKS_Released,
        eKS_Pressed
    };
}

#endif // WEB_ENGINE_WINDOW_INPUT_KEY_STATE_HPP_