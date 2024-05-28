#pragma once
#ifndef WEB_ENGINE_RESOURCES_LEVELS_BASE_OBJECT_HPP_
#define WEB_ENGINE_RESOURCES_LEVELS_BASE_OBJECT_HPP_

#include <glm/glm.hpp>

namespace WebEngine::Resources::Levels
{
    class BaseObject
    {
    public:
        BaseObject() = default;
        virtual ~BaseObject() = default;

        BaseObject( const BaseObject& other )             = delete;
        BaseObject( BaseObject&& other )                  = delete;
        BaseObject& operator=( const BaseObject& other )  = delete;
        BaseObject& operator=( const BaseObject&& other ) = delete;

        void move( const glm::vec3& distance );
        void rotateRad( const glm::vec3& radians );
        void rotateDeg( const glm::vec3& degrees );
        void scale( const glm::vec3& scale );

        void setPosition( glm::vec3 position ) { m_position = position; }
        void setRotationRad( glm::vec3 radians ) { m_rotation = radians; }
        void setRotationDeg( glm::vec3 degrees ) { setRotationRad( glm::radians( degrees) ); }
        void setScale( glm::vec3 scale ) { m_scale = scale; }

        const glm::vec3& getPosition() const { return m_position; }
        const glm::vec3& getRotationRad() const { return m_rotation; }
        glm::vec3 getRotationDeg() const { return glm::degrees( m_rotation ); }
        const glm::vec3& getScale() const { return m_scale; }

        virtual glm::mat4 getModel() const;

    private:
        glm::vec3 m_position = glm::vec3( 0.0f );
        glm::vec3 m_rotation = glm::vec3( 0.0f );
        glm::vec3 m_scale = glm::vec3( 1.0f );

    };
}

#endif // WEB_ENGINE_RESOURCES_LEVELS_BASE_OBJECT_HPP_