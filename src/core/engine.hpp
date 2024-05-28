#pragma once
#ifndef WEB_ENGINE_CORE_ENGINE_HPP_
#define WEB_ENGINE_CORE_ENGINE_HPP_

#include <memory>

namespace WebEngine::Core::OpenGL { class Renderer; }
namespace WebEngine::Core::Utils { class Clock; }
namespace WebEngine::Resources::Levels { class DefaultLevel; class HouseScene; }
namespace WebEngine::Window { class SDL2; }

namespace WebEngine::Core
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        Engine( const Engine& other )             = delete;
        Engine( Engine&& other )                  = delete;
        Engine& operator=( const Engine& other )  = delete;
        Engine& operator=( const Engine&& other ) = delete;

        void run();

    private:
        void init();
        void mainLoop();

        static void mainLoopStatic( void* args );

        std::unique_ptr< Utils::Clock > m_clock = nullptr;
        std::unique_ptr< OpenGL::Renderer > m_renderer = nullptr;
        std::unique_ptr< Resources::Levels::DefaultLevel > m_defaultLevel = nullptr;
        std::unique_ptr< Resources::Levels::HouseScene > m_houseScene = nullptr;
    };
}

#endif // WEB_ENGINE_CORE_ENGINE_HPP_