#include "sdl2.hpp"

#include <iostream>
#include <stdexcept>

namespace WebEngine::Window
{
    SDL2::SDL2( Settings::SDL2Settings settings )
        : m_settings { settings }
    {
        if ( settings.MajorVersionOpenGL > 2 )
        {
            throw std::runtime_error( "Web Assembly doesn't support OpenGL > 2" );
        }

        if ( settings.Size.x  < 0 || settings.Size.y < 0 )
        {
            throw std::runtime_error( "Window size can't be less then 0" );
        }

        if ( SDL_Init( SDL_INIT_VIDEO ) )
        {
            SDL_Quit();
            throw std::runtime_error( SDL_GetError() );
        }

        m_window = SDL_CreateWindow( "",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            settings.Size.x,
            settings.Size.y,
            static_cast< Uint32 >( settings.Flags ) );

        if ( !m_window )
        {
            SDL_Quit();
            throw std::runtime_error( SDL_GetError() );
        }

        m_windowID = SDL_GetWindowID( m_window );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, settings.MajorVersionOpenGL );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, settings.MinorVersionOpenGL );
        SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, settings.Samples );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, settings.DoubleBuffer );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, settings.DepthSize );

        m_context = SDL_GL_CreateContext( m_window );

        if ( m_context == NULL )
        {
            SDL_DestroyWindow( m_window );
            m_window = nullptr;
            SDL_Quit();
            throw std::runtime_error( SDL_GetError() );
        }
    }

    SDL2::~SDL2()
    {
        destroyWindow();
        SDL_Quit();
    }

    void SDL2::destroyWindow()
    {
        if ( m_window )
        {
            SDL_GL_DeleteContext(m_context);
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }

    void SDL2::pollEvents()
    {
        SDL_Event event;

        while ( SDL_PollEvent( &event ) )
        {
            switch ( event.type )
            {
                case SDL_KEYDOWN:
                {
                    keyPressedEvent.invoke( static_cast< Input::EKey >( event.key.keysym.sym ) );
                    break;
                }
                case SDL_KEYUP:
                {
                    keyReleasedEvent.invoke( static_cast< Input::EKey >( event.key.keysym.sym ) );
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    mouseButtonPressedEvent.invoke( static_cast< Input::EMouseButton >( event.button.button ) );
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    mouseButtonReleasedEvent.invoke( static_cast< Input::EMouseButton >( event.button.button ) );
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    cursorMoveEvent.invoke( glm::i32vec2( event.motion.x, event.motion.y ) );
                    break;
                }
                case SDL_WINDOWEVENT:
                {
                    switch ( event.window.event )
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                        {
                            resizeEvent.invoke( glm::i32vec2( event.window.data1, event.window.data2 ) );
                            break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_GAINED:
                        {
                            gainFocusEvent.invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_LOST:
                        {
                            lostFocusEvent.invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_CLOSE:
                        {
                            closeEvent.invoke();
                            destroyWindow();
                            break;
                        }
                    }
                    break;
                }
                case SDL_QUIT:
                {
                    destroyWindow();
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    glm::i32vec2 SDL2::getWindowSize()
    {
        glm::i32vec3 size;
        SDL_GetWindowSize( m_window, &size.x, &size.y );
        return size;
    }

    glm::i32vec2 SDL2::getMousePosition()
    {
        glm::i32vec2 result;
        SDL_GetMouseState( &result.x, &result.y );
        return result;
    }
}
