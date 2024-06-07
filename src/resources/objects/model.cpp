#include "resources/objects/model.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace WebEngine::Resources::Objects
{
    Model::Model( std::map< std::string, MeshPtr >& meshes )
    {
        m_meshes = std::move( meshes );
    }

    Model::~Model()
    {
        for ( auto& mesh : m_meshes )
            mesh.second = nullptr;

        m_meshes.clear();
    }

    Geometry::Mesh& Model::getMesh( const std::string& mesh )
    {
        if ( !m_meshes.count( mesh ) )
            throw std::runtime_error( "Mesh doesn't exist" );

        return *( m_meshes[ mesh ].get() );
    }

    void Model::draw( const Shaders::Shader& shader ) const
    {
        shader.setMat4( "normalMatrix", glm::transpose( glm::inverse( getModel() ) ) );

        for ( const auto& mesh : m_meshes )
        {
            mesh.second->draw( shader );
        }
    }
}
