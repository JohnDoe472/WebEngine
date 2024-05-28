#pragma once
#ifndef WEB_ENGINE_RESOURCES_OBJECTS_LIGHT_SOURCE_HPP_
#define WEB_ENGINE_RESOURCES_OBJECTS_LIGHT_SOURCE_HPP_

#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "resources/geometry/mesh.hpp"
#include "resources/levels/base_object.hpp"
#include "resources/shaders/shader.hpp"

namespace WebEngine::Resources::Objects
{
    class LightSource : public Levels::BaseObject
    {
        using MeshPtr = std::unique_ptr< Geometry::Mesh >;
        
    public:
        LightSource();
        ~LightSource();

        LightSource( const LightSource& other )             = delete;
        LightSource( LightSource&& other )                  = delete;
        LightSource& operator=( const LightSource& other )  = delete;
        LightSource& operator=( const LightSource&& other ) = delete;

        void draw( const Shaders::Shader& shader ) const;

    private:
        uint32_t m_vbo = 0;
    };
}

#endif // WEB_ENGINE_RESOURCES_OBJECTS_LIGHT_SOURCE_HPP_
