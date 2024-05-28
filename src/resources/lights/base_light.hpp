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

        void setAmbient( glm::vec3 ambient ) { m_ambient = ambient; }
        void setDiffuse( glm::vec3 diffuse ) { m_diffuse = diffuse; }
        void setSpecular( glm::vec3 specular ) { m_specular = specular; }
        void setColor( glm::vec3 color ) { m_color = color; }

        glm::vec3 getAmbient() const { return m_ambient * m_color; }
        glm::vec3 getDiffuse() const { return m_diffuse * m_color; }
        glm::vec3 getSpecular() const { return m_specular * m_color; }
        const glm::vec3& getColor() const { return m_color; }

    private:
        glm::vec3 m_ambient = glm::vec3( 0.05f );
        glm::vec3 m_diffuse = glm::vec3( 1.0f );
        glm::vec3 m_specular = glm::vec3( 1.0f );
        glm::vec3 m_color = glm::vec3( 1.0f );
    };
}

#endif // WEB_ENGINE_RESOURCES_LIGHTS_BASE_LIGHT_HPP_