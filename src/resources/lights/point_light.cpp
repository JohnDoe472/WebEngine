#include "resources/lights/point_light.hpp"

namespace WebEngine::Resources::Lights
{
    PointLight::PointLight()
    {
        m_lightSource = std::make_unique< Objects::LightSource >();
        m_lightSource->setScale( glm::vec3( 0.5f ) );
    }

    PointLight::~PointLight()
    {
        if ( m_lightSource )
            m_lightSource = nullptr;
    }

    void PointLight::draw( const Shaders::Shader& shader ) const
    {
        if ( m_lightSource )
        {
            shader.setMat4( "model", m_lightSource->getModel() );
            shader.setVec4( "color", glm::vec4( getColorRGB(), 1.0f ) );
            m_lightSource->draw( shader );
        }
    }

}
