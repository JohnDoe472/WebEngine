#include "resources/cameras/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace WebEngine::Resources::Cameras
{
    Camera::Camera( float width, float height, float fov, float near, float far )
        : m_width { width },
          m_height { height },
          m_fov { fov },
          m_near { near },
          m_far { far }
    {

    }

    glm::mat4 Camera::getProjectionMatrix() const
    {
        if ( m_projectionMode == EProjectionMode::ePM_Orthographic )
            return glm::ortho( 0.0f, m_width, m_height, 0.0f, m_near, m_far );

        return glm::perspective( m_fov, m_width / m_height, m_near, m_far );
    }

    glm::mat4 Camera::getViewMatrix() const
    {
        glm::vec3 up = glm::quat( m_rotation ) * glm::vec3( 0.0f, 1.0f, 0.0f );
        glm::vec3 forward = glm::quat( m_rotation ) * glm::vec3( 0.0f, 0.0f, -1.0f );

        return glm::lookAt( m_position, m_position + forward, up );
    }

    void Camera::move( const glm::vec3& direction )
    {
        m_position += direction;
    }

    void Camera::rotate( const glm::vec3& angle )
    {
        m_rotation += angle;
    }
}
