#include "resources/shaders/shader.hpp"
#include "core/parsers/shader_reader.hpp"

#include <SDL2/SDL_opengles2.h>

namespace WebEngine::Resources::Shaders
{
    Shader::Shader( ShaderLocation location )
        : m_shaderLocation { location },
        Id { Core::Parsers::ShaderReader::readShader( location ) }
    {
        
    }

    Shader::~Shader()
    {
        glDeleteProgram( Id );
    }

    void Shader::bind() const
    {
        glUseProgram( Id );
    }

    void Shader::unbind() const
    {
        glUseProgram( 0 );
    }

    void Shader::setBool( const std::string& name, bool value ) const
    {
        glUniform1i( glGetUniformLocation( Id, name.c_str() ), static_cast< int >( value ) );
    }

    void Shader::setInt( const std::string& name, int value ) const
    { 
        glUniform1i( glGetUniformLocation( Id, name.c_str() ), value );
    }

    void Shader::setFloat( const std::string& name, float value ) const
    { 
        glUniform1f( glGetUniformLocation( Id, name.c_str() ), value );
    }

    void Shader::setVec2( const std::string& name, const glm::vec2& value ) const
    { 
        glUniform2fv( glGetUniformLocation( Id, name.c_str() ), 1, &value[ 0 ] );
    }

    void Shader::setVec2( const std::string& name, float x, float y ) const
    { 
        glUniform2f( glGetUniformLocation( Id, name.c_str() ), x, y );
    }

    void Shader::setVec3( const std::string& name, const glm::vec3& value ) const
    { 
        glUniform3fv( glGetUniformLocation( Id, name.c_str() ), 1, &value[ 0 ] );
    }

    void Shader::setVec3( const std::string& name, float x, float y, float z ) const
    { 
        glUniform3f( glGetUniformLocation( Id, name.c_str() ), x, y, z );
    }

    void Shader::setVec4( const std::string& name, const glm::vec4& value ) const
    { 
        glUniform4fv( glGetUniformLocation( Id, name.c_str() ), 1, &value[ 0 ] );
    }

    void Shader::setVec4( const std::string& name, float x, float y, float z, float w ) const
    { 
        glUniform4f( glGetUniformLocation( Id, name.c_str() ), x, y, z, w );
    }

    void Shader::setMat2( const std::string& name, const glm::mat2& mat ) const
    {
        glUniformMatrix2fv( glGetUniformLocation( Id, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
    }

    void Shader::setMat3( const std::string& name, const glm::mat3& mat ) const
    {
        glUniformMatrix3fv( glGetUniformLocation( Id, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
    }

    void Shader::setMat4( const std::string& name, const glm::mat4& mat ) const
    {
        glUniformMatrix4fv( glGetUniformLocation( Id, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
    }
}
