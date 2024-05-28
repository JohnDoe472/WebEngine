#pragma once
#ifndef WEB_ENGINE_CORE_PARSERS_SHADER_READER_HPP_
#define WEB_ENGINE_CORE_PARSERS_SHADER_READER_HPP_

#include <filesystem>

#include "resources/shaders/shader.hpp"
#include "resources/shaders/shader_type.hpp"

namespace WebEngine::Core::Parsers
{
    class ShaderReader
    {
    public:
        static uint32_t readShader( Resources::Shaders::ShaderLocation location );
        
    private:
        static uint32_t compileShader( std::filesystem::path path, Resources::Shaders::EShaderType type );
        static void raiseProgramError( uint32_t id );
        static void raiseShaderError( uint32_t id, Resources::Shaders::EShaderType type );
    };
}

#endif // WEB_ENGINE_CORE_PARSERS_SHADER_READER_HPP_
