#include "resources/levels/base_object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace WebEngine::Resources::Levels
{
    void BaseObject::move( const glm::vec3& distance )
    {
        m_position += distance;
    }

    void BaseObject::rotateRad( const glm::vec3& radians )
    {
        m_rotation += radians;
    }

    void BaseObject::rotateDeg( const glm::vec3& degrees )
    {
        rotateRad( glm::radians( degrees ) );
    }

    void BaseObject::scale( const glm::vec3& scale )
    {
        m_scale = scale;
    }

    glm::mat4 BaseObject::getModel() const
    {
        glm::mat4 model = glm::mat4( 1.0f );

        model = glm::translate( model, m_position );
        model *= glm::mat4_cast( glm::quat( m_rotation ) );
        model = glm::scale( model, m_scale );

        return model;
    }
}
