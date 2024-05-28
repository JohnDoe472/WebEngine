#include "shader_reader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Parsers = WebEngine::Core::Parsers;
namespace Shaders = WebEngine::Resources::Shaders;

uint32_t Parsers::ShaderReader::readShader( Shaders::ShaderLocation location )
{
    const uint32_t newShader = glCreateProgram();

    const uint32_t vs = compileShader( location.VertexShaderPath, Shaders::EShaderType::eST_Vertex );
    const uint32_t fs = compileShader( location.FragmentShaderPath, Shaders::EShaderType::eST_Fragment );

    if ( vs == 0 || fs == 0 )
    {
        std::cout << "ERROR: Shaders are 0" << std::endl; 
        throw std::runtime_error( "Shaders are 0" );
    }

    glAttachShader( newShader, vs );
    glAttachShader( newShader, fs );
    
    glLinkProgram( newShader );

    GLint linkStatus;
    glGetProgramiv( newShader, GL_LINK_STATUS, &linkStatus );

    if ( linkStatus == GL_FALSE )
        raiseProgramError( newShader );

    glValidateProgram( newShader );
    glDeleteShader( vs );
    glDeleteShader( fs );

    return newShader;
}

uint32_t Parsers::ShaderReader::compileShader( std::filesystem::path path, Shaders::EShaderType type )
{
    const uint32_t id = glCreateShader( static_cast< int >( type ) );

    std::ifstream file;
    file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    file.open( path.string() );

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    std::string code = stream.str();
    const char* tmp = code.c_str();
    glShaderSource( id, 1, &tmp, nullptr );
    glCompileShader( id );

    GLint compileStatus;
    glGetShaderiv( id, GL_COMPILE_STATUS, &compileStatus );

    if ( compileStatus == GL_FALSE )
        raiseShaderError( id, type );

    return id;
}

void Parsers::ShaderReader::raiseProgramError( uint32_t id )
{
    GLint maxLength;
    glGetProgramiv( id, GL_INFO_LOG_LENGTH, &maxLength );

    std::string errorLog( maxLength, ' ' );
    glGetProgramInfoLog( id, maxLength, &maxLength, errorLog.data() );

    glDeleteProgram( id );

    std::cout << errorLog << std::endl;
    throw std::runtime_error( errorLog );
}

void Parsers::ShaderReader::raiseShaderError( uint32_t id, Shaders::EShaderType type )
{
    GLint maxLength;
    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &maxLength );

    std::string errorLog( maxLength, ' ' );
    glGetShaderInfoLog( id, maxLength, &maxLength, errorLog.data() );

    std::string shaderTypeString = "VERTEX SHADER";

    if ( type == Shaders::EShaderType::eST_Fragment )
        shaderTypeString = "FRAGMENT SHADER";

    std::string errorHeader = "[" + shaderTypeString + "] \"" + errorLog + "\"";

    glDeleteShader( id );

    std::cout << errorHeader << std::endl;
    throw std::runtime_error( errorHeader );
}
