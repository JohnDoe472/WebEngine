#pragma once
#ifndef WEB_ENGINE_RESOURCES_LIGHTS_DIRECTIONAL_LIGHT_HPP_
#define WEB_ENGINE_RESOURCES_LIGHTS_DIRECTIONAL_LIGHT_HPP_

#include "resources/lights/base_light.hpp"

namespace WebEngine::Resources::Lights
{
    class DirectionalLight : public BaseLight
    {
    public:
        DirectionalLight() = default;
        virtual ~DirectionalLight() = default;

        DirectionalLight( const DirectionalLight& other )             = delete;
        DirectionalLight( DirectionalLight&& other )                  = delete;
        DirectionalLight& operator=( const DirectionalLight& other )  = delete;
        DirectionalLight& operator=( const DirectionalLight&& other ) = delete;

        void setDirection( glm::vec3 direction ) { m_direction = direction; }
        const glm::vec3& getDirection() const { return m_direction; }

    private:
        glm::vec3 m_direction = glm::vec3( 0.0f );
    };
}

#endif // WEB_ENGINE_RESOURCES_LIGHTS_DIRECTIONAL_LIGHT_HPP_