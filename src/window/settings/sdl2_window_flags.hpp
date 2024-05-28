#pragma once
#ifndef WEB_ENGINE_WINDOW_SETTINGS_SDL2_WINDOW_FLAGS_HPP_
#define WEB_ENGINE_WINDOW_SETTINGS_SDL2_WINDOW_FLAGS_HPP_

#include <stdint.h>

namespace WebEngine::Window::Settings
{
    enum class ESDL2WindowFlags : uint32_t
    {
        eSDL2WF_None              = 0x00000000,
        eSDL2WF_Fullscreen        = 0x00000001,
        eSDL2WF_OpenGL            = 0x00000002,
        eSDL2WF_Shown             = 0x00000004,
        eSDL2WF_Hidden            = 0x00000008,
        eSDL2WF_Borderless        = 0x00000010,
        eSDL2WF_Resizable         = 0x00000020,
        eSDL2WF_Minimized         = 0x00000040,
        eSDL2WF_Maximized         = 0x00000080,
        eSDL2WF_MouseGrabbed      = 0x00000100,
        eSDL2WF_InputFocus        = 0x00000200,
        eSDL2WF_MouseFocus        = 0x00000400,
        eSDL2WF_FullscreenDesktop = (eSDL2WF_Fullscreen | 0x00001000),
        eSDL2WF_Foreign           = 0x00000800,
        eSDL2WF_AllowHighdpi      = 0x00002000,
        eSDL2WF_MouseCapture      = 0x00004000,
        eSDL2WF_AlwaysOnTop       = 0x00008000,
        eSDL2WF_SkipTaskbar       = 0x00010000,
        eSDL2WF_Utility           = 0x00020000,
        eSDL2WF_Tooltip           = 0x00040000,
        eSDL2WF_PopupMenu         = 0x00080000,
        eSDL2WF_KeyboardGrabbed   = 0x00100000,
        eSDL2WF_Vulkan            = 0x10000000,
        eSDL2WF_Metal             = 0x20000000,
        eSDL2WF_InputGrabbed      = eSDL2WF_MouseGrabbed
    };

    inline ESDL2WindowFlags operator~   (ESDL2WindowFlags  a) { return (ESDL2WindowFlags)~static_cast<int>(a); }
    inline ESDL2WindowFlags operator|   (ESDL2WindowFlags  a, ESDL2WindowFlags b) { return (ESDL2WindowFlags)(static_cast<int>(a) | static_cast<int>(b)); }
    inline ESDL2WindowFlags operator&   (ESDL2WindowFlags  a, ESDL2WindowFlags b) { return (ESDL2WindowFlags)(static_cast<int>(a) & static_cast<int>(b)); }
    inline ESDL2WindowFlags operator^   (ESDL2WindowFlags  a, ESDL2WindowFlags b) { return (ESDL2WindowFlags)(static_cast<int>(a) ^ static_cast<int>(b)); }
    inline ESDL2WindowFlags& operator|= (ESDL2WindowFlags& a, ESDL2WindowFlags b) { return (ESDL2WindowFlags&)((int&)a |= static_cast<int>(b)); }
    inline ESDL2WindowFlags& operator&= (ESDL2WindowFlags& a, ESDL2WindowFlags b) { return (ESDL2WindowFlags&)((int&)a &= static_cast<int>(b)); }
    inline ESDL2WindowFlags& operator^= (ESDL2WindowFlags& a, ESDL2WindowFlags b) { return (ESDL2WindowFlags&)((int&)a ^= static_cast<int>(b)); }
}

#endif // WEB_ENGINE_WINDOW_SETTINGS_SDL2_WINDOW_FLAGS_HPP_
