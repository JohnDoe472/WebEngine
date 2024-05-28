#pragma once
#ifndef WEB_ENGINE_CORE_OPEN_GL_RENDERER_HPP_
#define WEB_ENGINE_CORE_OPEN_GL_RENDERER_HPP_

namespace WebEngine::Core::OpenGL
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() { }

        Renderer( const Renderer& other )             = delete;
        Renderer( Renderer&& other )                  = delete;
        Renderer& operator=( const Renderer& other )  = delete;
        Renderer& operator=( const Renderer&& other ) = delete;

        void prepareFrame() const;
    };
}

#endif // WEB_ENGINE_CORE_OPEN_GL_RENDERER_HPP_