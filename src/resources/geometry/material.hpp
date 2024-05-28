#pragma once
#ifndef WEB_ENGINE_RESOURCES_GEOMETRY_MATERIAL_HPP_
#define WEB_ENGINE_RESOURCES_GEOMETRY_MATERIAL_HPP_

#include <memory>
#include <string>

#include "resources/textures/texture.hpp"
#include "resources/shaders/shader.hpp"

namespace WebEngine::Resources::Geometry
{
    class Material
    {        
        using TexturePtr = std::unique_ptr< Textures::Texture >;

    public:
        Material( std::string name = "default" ) : m_name { name } { }
        ~Material();

        Material( const Material& other )             = delete;
        Material( Material&& other )                  = delete;
        Material& operator=( const Material& other )  = delete;
        Material& operator=( const Material&& other ) = delete;

        void bind( const Shaders::Shader& shader ) const;
        void unbind() const;

        const std::string& getName() const { return m_name; }

        const TexturePtr& getAlbedo()    const { return m_albedo; }
        const TexturePtr& getNormal()    const { return m_normal; }
        const TexturePtr& getMetallic()  const { return m_metallic; }
        const TexturePtr& getRoughness() const { return m_roughness; }
        const TexturePtr& getAO()        const { return m_ao; }

        void loadAlbedo( const std::filesystem::path& albedoPath );
        void loadNormal( const std::filesystem::path& normalPath );
        void loadMetallic( const std::filesystem::path& metallicPath );
        void loadRougness( const std::filesystem::path& roughnessPath );
        void loadAO( const std::filesystem::path& aoPath );

    private:
        std::string m_name = "default";

        TexturePtr m_albedo    = nullptr;
        TexturePtr m_normal    = nullptr;
        TexturePtr m_metallic  = nullptr;
        TexturePtr m_roughness = nullptr;
        TexturePtr m_ao        = nullptr;
    };
}

#endif // WEB_ENGINE_RESOURCES_GEOMETRY_MATERIAL_HPP_