#pragma once
#ifndef WEB_ENGINE_WINDOW_SDL2_HPP_
#define WEB_ENGINE_WINDOW_SDL2_HPP_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "core/eventing/event.hpp"
#include "core/services/service_interface.hpp"
#include "window/input/key.hpp"
#include "window/input/mouse_button.hpp"
#include "window/settings/sdl2_settings.hpp"

namespace WebEngine::Window
{
    class SDL2 : public Core::Services::IService
    {
    public:
        SDL2( Settings::SDL2Settings settings );
        virtual ~SDL2();

        SDL2( const SDL2& other )             = delete;
        SDL2( SDL2&& other )                  = delete;
        SDL2& operator=( const SDL2& other )  = delete;
        SDL2& operator=( const SDL2&& other ) = delete;

        void pollEvents();

        void swapBuffers() const { SDL_GL_SwapWindow( m_window ); }

        void showCursor( bool state )                  { SDL_ShowCursor( state ? SDL_ENABLE : SDL_DISABLE ); }
        void setRelativeMouseMode( bool lock )         { SDL_SetRelativeMouseMode( lock ? SDL_TRUE : SDL_FALSE ); }
        void setMousePosition( glm::i32vec2 position ) { SDL_WarpMouseInWindow( m_window, position.x, position.y ); }

        glm::i32vec2 getWindowSize();
        glm::i32vec2 getMousePosition();

        Core::Eventing::Event< Input::EKey > keyPressedEvent;
        Core::Eventing::Event< Input::EKey > keyReleasedEvent;
        Core::Eventing::Event< Input::EMouseButton > mouseButtonPressedEvent;
        Core::Eventing::Event< Input::EMouseButton > mouseButtonReleasedEvent;

        Core::Eventing::Event< glm::i32vec2 > resizeEvent;
        Core::Eventing::Event< glm::i32vec2 > cursorMoveEvent;
        Core::Eventing::Event<> gainFocusEvent;
        Core::Eventing::Event<> lostFocusEvent;
        Core::Eventing::Event<> closeEvent;

    private:
        void destroyWindow();

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context;

        Settings::SDL2Settings m_settings;

        uint32_t m_windowID = 0;
    };
}

#endif // WEB_ENGINE_WINDOW_SDL2_HPP_