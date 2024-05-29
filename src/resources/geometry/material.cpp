#include "resources/geometry/material.hpp"
#include "core/parsers/texture_reader.hpp"

#include <iostream>

namespace WebEngine::Resources::Geometry
{
    Material::~Material()
    {
        if ( m_albedo )
            m_albedo = nullptr;
        
        if ( m_normal )
            m_normal = nullptr;
        
        if ( m_metallic )
            m_metallic = nullptr;
        
        if ( m_roughness )
            m_roughness = nullptr;
        
        if ( m_ao )
            m_ao = nullptr;
    }

    void Material::bind( const Shaders::Shader& shader ) const
    {
        shader.setInt( "material.albedo", 0 );
        shader.setInt( "material.normal", 1 );
        shader.setInt( "material.metallic", 2 );
        shader.setInt( "material.roughness", 3 );
        shader.setInt( "material.ao", 4 );

        if ( m_albedo )
            m_albedo->bind( 0 );

        if ( m_normal )
        {
            shader.setInt( "material.normalExist", 1 );
            m_normal->bind( 1 );
        }
        else
            shader.setInt( "material.normalExist", 0 );

        if ( m_metallic )
        {
            shader.setInt( "material.metallicExist", 1 );
            m_metallic->bind( 2 );
        }
        else
            shader.setInt( "material.metallicExist", 0 );

        if ( m_roughness )
        {
            shader.setInt( "material.roughnessExist", 1 );
            m_roughness->bind( 3 );
        }
        else
            shader.setInt( "material.roughnessExist", 0 );

        if ( m_ao )
        {
            shader.setInt( "material.aoExist", 1 );
            m_ao->bind( 4 );
        }
        else
            shader.setInt( "material.aoExist", 0 );
    }

    void Material::unbind() const
    {
        if ( m_albedo )
            m_albedo->unbind( 0 );

        if ( m_normal )
            m_normal->unbind( 1 );

        if ( m_metallic )
            m_metallic->unbind( 2 );

        if ( m_roughness )
            m_roughness->unbind( 3 );

        if ( m_ao )
            m_ao->unbind( 4 );
    }

    void Material::loadAlbedo( const std::filesystem::path& albedoPath )
    {
        if ( !std::filesystem::exists( albedoPath ) )
            return;

        if ( m_albedo )
            m_albedo = nullptr;

        m_albedo = std::move( Core::Parsers::TextureReader::loadTexture( albedoPath ) );
    }

    void Material::loadNormal( const std::filesystem::path& normalPath )
    {
        if ( !std::filesystem::exists( normalPath ) ) {
            std::cout << "texture not found: " << normalPath << std::endl;
            return;
        }

        if ( m_normal )
            m_normal = nullptr;

        m_normal = std::move( Core::Parsers::TextureReader::loadTexture( normalPath ) );
    }

    void Material::loadMetallic( const std::filesystem::path& metallicPath )
    {
        if ( !std::filesystem::exists( metallicPath ) ) {
            std::cout << "texture not found: " << metallicPath << std::endl;
            return;
        }

        if ( m_metallic )
            m_metallic = nullptr;

        m_metallic = std::move( Core::Parsers::TextureReader::loadTexture( metallicPath ) );
    }

    void Material::loadRougness( const std::filesystem::path& roughnessPath )
    {
        if ( !std::filesystem::exists( roughnessPath ) ) {
            std::cout << "texture not found: " << roughnessPath << std::endl;
            return;
        }

        if ( m_roughness )
            m_roughness = nullptr;

        m_roughness = std::move( Core::Parsers::TextureReader::loadTexture( roughnessPath ) );
    }

    void Material::loadAO( const std::filesystem::path& aoPath )
    {
        if ( !std::filesystem::exists( aoPath ) ) {
            std::cout << "texture not found: " << aoPath << std::endl;
            return;
        }

        if ( m_ao )
            m_ao = nullptr;
        
        m_ao = std::move( Core::Parsers::TextureReader::loadTexture( aoPath ) );
    }
}