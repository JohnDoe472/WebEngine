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

        void setConstant( float constant ) { m_constant = constant; }
        void setLinear( float linear ) { m_linear = linear; }
        void setQuadratic( float quadratic ) { m_quadratic = quadratic; }
        void setPosition( glm::vec3 position ) { m_lightSource->setPosition( position ); }
        void setScale( glm::vec3 scale ) { m_lightSource->setScale( scale ); }
        
        const float& getConstant() const { return m_constant; }
        const float& getLinear() const { return m_linear; }
        const float& getQuadratic() const { return m_quadratic; }
        const glm::vec3& getPosition() const { return m_lightSource->getPosition(); }
        const glm::vec3& getScale() const { return m_lightSource->getScale(); }

    private:
        float m_constant  = 1.0f;
        float m_linear    = 0.09f;
        float m_quadratic = 0.032f;

        LightSourcePtr m_lightSource = nullptr;
    };
}

#endif // WEB_ENGINE_RESOURCES_LIGHTS_POINT_LIGHT_HPP_