#pragma once
#ifndef WEB_ENGINE_RESOURCES_SHADERS_SHADER_TYPE_HPP_
#define WEB_ENGINE_RESOURCES_SHADERS_SHADER_TYPE_HPP_

#include <SDL2/SDL_opengles2.h>

namespace WebEngine::Resources::Shaders
{
    enum class EShaderType
    {
        eST_Vertex   = GL_VERTEX_SHADER,
        eST_Fragment = GL_FRAGMENT_SHADER
        // OpenGLES 2.0 doesn't support Geometry Shader
        // eST_Geometry = GL_GEOMETRY_SHADER
    };
}

#endif // WEB_ENGINE_RESOURCES_SHADERS_SHADER_TYPE_HPP_
