#pragma once
#ifndef WEB_ENGINE_RESOURCES_LIGHTS_POINT_LIGHT_HPP_
#define WEB_ENGINE_RESOURCES_LIGHTS_POINT_LIGHT_HPP_

#include "resources/lights/base_light.hpp"
#include "resources/objects/light_source.hpp"

namespace WebEngine::Resources::Lights
{
    class PointLight : public BaseLight
    {
        using LightSourcePtr = std::unique_ptr< Objects::LightSource >;

    public:
        PointLight();
        virtual ~PointLight();

        PointLight( const PointLight& other )             = delete;
        PointLight( PointLight&& other )                  = delete;
        PointLight& operator=( const PointLight& other )  = delete;
        PointLight& operator=( const PointLight&& other ) = delete;

        void draw( const Shaders::Shader& shader ) const;

        const glm::vec3& getAttenuation() const { return m_attenuation; }
        void setAttenuation( glm::vec3 attenuation ) { m_attenuation = attenuation; }

        void setPosition( glm::vec3 position ) { m_lightSource->setPosition( position ); }
        const glm::vec3& getPosition() const { return m_lightSource->getPosition(); }

        void setScale( glm::vec3 scale ) { m_lightSource->setScale( scale ); }
        const glm::vec3& getScale() const { return m_lightSource->getScale(); }

    private:
        glm::vec3 m_attenuation = glm::vec3( 1.0f, 0.09f, 0.032f );

        LightSourcePtr m_lightSource = nullptr;
    };
}

#endif // WEB_ENGINE_RESOURCES_LIGHTS_POINT_LIGHT_HPP_