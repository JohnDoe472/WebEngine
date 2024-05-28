#pragma once
#ifndef WEB_ENGINE_CORE_UTILS_CLOCK_HPP_
#define WEB_ENGINE_CORE_UTILS_CLOCK_HPP_

#include <chrono>

namespace WebEngine::Core::Utils
{
    class Clock
    {
    public:
        Clock() { initialize(); }
        ~Clock() { }

        Clock( const Clock& other )             = delete;
        Clock( Clock&& other )                  = delete;
        Clock& operator=( const Clock& other )  = delete;
        Clock& operator=( const Clock&& other ) = delete;

        void update()
        {
            m_lastTime = m_currentTime;
            m_currentTime = std::chrono::steady_clock::now();
            m_elapsed = m_currentTime - m_lastTime;

            if ( m_isInit )
            {
                m_deltaTime = m_elapsed.count() > 0.1 ? 0.1f : static_cast< float >( m_elapsed.count() );
                m_timeSinceStart += m_deltaTime * m_timeScale;
            }
            else
                initialize();
        }

        float getFramerate()         { return 1.0f / m_deltaTime; }
        float getDeltaTime()         { return m_deltaTime * m_timeScale; }
        float getDeltaTimeUnscaled() { return m_deltaTime; }
        float getTimeSinceStart()    { return m_timeSinceStart; }
        float getTimeScale()         { return m_timeScale; }

        void scale( float coeff ) { m_timeScale *= coeff; }

        void setTimeScale( float timeScale ) { m_timeScale = timeScale; }

    private:
        void initialize()
        {
            m_deltaTime = 0.0f;

            m_startTime = std::chrono::steady_clock::now();
            m_currentTime = m_startTime;
            m_lastTime = m_startTime;

            m_isInit = true;
        }

        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_lastTime;
        std::chrono::steady_clock::time_point m_currentTime;
        std::chrono::duration< double >       m_elapsed;

        bool  m_isInit         = false;
        float m_timeScale      = 1.0f;
        float m_deltaTime      = 0.0f;
        float m_timeSinceStart = 0.0f;
    };
}

#endif // WEB_ENGINE_CORE_UTILS_CLOCK_HPP_