#include "core/engine.hpp"
#include "core/open_gl/renderer.hpp"
#include "core/services/service_locator.hpp"
#include "core/utils/clock.hpp"
#include "resources/levels/default_level.hpp"
#include "resources/levels/house_scene.hpp"
#include "window/sdl2.hpp"

#include <iostream>
#include <stdexcept>

#include <emscripten.h>

namespace WebEngine::Core
{
    Engine::Engine()
    {
        init();
    }

    Engine::~Engine()
    {
        if ( m_defaultLevel )
            m_defaultLevel = nullptr;

        if ( m_renderer )
            m_renderer = nullptr;
            
        if ( m_clock )
            m_clock = nullptr;
    }

    void Engine::init()
    {
        m_clock = std::make_unique< Utils::Clock >();

        Window::Settings::SDL2Settings settings;
        settings.Size               = { 1280, 720 };
        settings.MajorVersionOpenGL = 2;
        settings.MinorVersionOpenGL = 0; 
        settings.Samples            = 4;
        settings.DoubleBuffer       = 1;
        settings.DepthSize          = 24;

        settings.Flags = Window::Settings::ESDL2WindowFlags::eSDL2WF_OpenGL    |
                         Window::Settings::ESDL2WindowFlags::eSDL2WF_Resizable |
                         Window::Settings::ESDL2WindowFlags::eSDL2WF_Shown;

        Services::ServiceLocator::provide< Window::SDL2 >( settings );

        m_renderer = std::make_unique< OpenGL::Renderer >();
        //m_defaultLevel = std::make_unique< Resources::Levels::DefaultLevel >();
        m_houseScene = std::make_unique< Resources::Levels::HouseScene >();
    }

    void Engine::run()
    {
        emscripten_set_main_loop_arg( Engine::mainLoopStatic, this, 0, true );
    }

    void Engine::mainLoopStatic( void* args )
    {
        Engine* engine = reinterpret_cast< Engine* >( args );

        if ( !engine )
            throw std::runtime_error( "Can't cast args to Engine inside main loop" );

        engine->mainLoop();
    }

    void Engine::mainLoop()
    {
        std::shared_ptr< Window::SDL2 > window = Services::ServiceLocator::get< Window::SDL2 >();

        window->pollEvents();
        m_renderer->prepareFrame();
        //m_defaultLevel->draw( m_clock->getDeltaTime() );
        m_houseScene->draw( m_clock->getDeltaTime() );
        window->swapBuffers();
    }
}
