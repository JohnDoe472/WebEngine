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

        void setColor( glm::vec3 color ) { m_color = color; }
        const glm::vec3& getColor() const { return m_color; }

    private:
        glm::vec3 m_color = glm::vec3( 1.0f );
    };
}

#endif // WEB_ENGINE_RESOURCES_LIGHTS_BASE_LIGHT_HPP_