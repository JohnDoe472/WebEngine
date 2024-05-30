#include "core/open_gl/renderer.hpp"

#include <SDL2/SDL_opengles2.h>

namespace WebEngine::Core::OpenGL
{
    Renderer::Renderer()
    {
        glEnable( GL_DEPTH_TEST );
    }

    void Renderer::prepareFrame() const
    {
        glClearColor( 0.0f, 0.2f, 0.4f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
    }
}
