#pragma once
#ifndef WEB_ENGINE_RESOURCES_CAMERAS_CAMERA_HPP_
#define WEB_ENGINE_RESOURCES_CAMERAS_CAMERA_HPP_

#include <glm/glm.hpp>

#include "resources/cameras/projection_mode.hpp"

namespace WebEngine::Resources::Cameras
{
    class Camera
    {
    public:
        Camera( float width, float height, float fov = 45.0f, float near = 0.1f, float far = 100.0f );
        ~Camera() = default;

        Camera( const Camera& other )             = delete;
        Camera( Camera&& other )                  = delete;
        Camera& operator=( const Camera& other )  = delete;
        Camera& operator=( const Camera&& other ) = delete;

        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getViewMatrix() const;
        EProjectionMode getProjectionMode() const { return m_projectionMode; }

        void move( const glm::vec3& direction );
        void rotate( const glm::vec3& angle );

        void setPosition( const glm::vec3& position ) { m_position = position; }
        const glm::vec3& getPosition() const { return m_position; }

        void setRotation( const glm::vec3& rotation ) { m_rotation = rotation; }
        const glm::vec3& getRotation() const { return m_rotation; }

    private:
        EProjectionMode m_projectionMode = EProjectionMode::ePM_Perspective;

        glm::vec3 m_position = glm::vec3( 0.0f );
        glm::vec3 m_rotation = glm::vec3( 0.0f );

        float m_width = 1280.0f;
        float m_height = 720.0f;
        float m_fov  = 45.0f;
        float m_near = 0.1f;
        float m_far  = 100.0f;
    };
}

#endif // WEB_ENGINE_RESOURCES_CAMERAS_CAMERA_HPP_
