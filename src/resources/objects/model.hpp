#pragma once
#ifndef WEB_ENGINE_RESOURCES_OBJECTS_MODEL_HPP_
#define WEB_ENGINE_RESOURCES_OBJECTS_MODEL_HPP_

#include <map>
#include <memory>
#include <string>

#include "resources/geometry/mesh.hpp"
#include "resources/levels/base_object.hpp"
#include "resources/shaders/shader.hpp"

namespace WebEngine::Resources::Objects
{
    class Model : public Levels::BaseObject
    {
        using MeshPtr = std::unique_ptr< Geometry::Mesh >;
        
    public:
        Model( std::map< std::string, MeshPtr >& meshes );
        ~Model();

        Model( const Model& other )             = delete;
        Model( Model&& other )                  = delete;
        Model& operator=( const Model& other )  = delete;
        Model& operator=( const Model&& other ) = delete;

        void draw( const Shaders::Shader& shader ) const;
        
        std::map< std::string, MeshPtr >& getMeshes() { return m_meshes; }
        Geometry::Mesh& getMesh( const std::string& mesh );

    private:
        std::map< std::string, MeshPtr > m_meshes;
    };
}

#endif // WEB_ENGINE_RESOURCES_OBJECTS_MODEL_HPP_
