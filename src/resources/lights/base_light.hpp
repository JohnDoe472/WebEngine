#pragma once
#ifndef WEB_ENGINE_RESOURCES_LIGHTS_BASE_LIGHT_HPP_
#define WEB_ENGINE_RESOURCES_LIGHTS_BASE_LIGHT_HPP_

#include <glm/glm.hpp>

namespace WebEngine::Resources::Lights
{
    class BaseLight
    {
    public:
        BaseLight() = default;
        virtual ~BaseLight() = default;

        BaseLight( const BaseLight& other )             = delete;
        BaseLight( BaseLight&& other )                  = delete;
        BaseLight& operator=( const BaseLight& other )  = delete;
        BaseLight& operator=( const BaseLight&& other ) = delete;

        void setColorRGB( glm::vec3 color ) { m_color = color; }
        void setIntensity( float intensity ) { m_intensity = intensity; }

        const glm::vec3& getColorRGB() const { return m_color; }
        const float& getIntensity() const { return m_intensity; }

    private:
        glm::vec3 m_color = glm::vec3( 255.0f );
        float m_intensity = 1.0f;
    };
}

#endif // WEB_ENGINE_RESOURCES_LIGHTS_BASE_LIGHT_HPP_